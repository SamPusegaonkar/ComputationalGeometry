from asyncio import FastChildWatcher
from node import Node
from domain import Domain
from tin import TIN
from point import Point

import math
import numpy as np
import matplotlib.pyplot as plt


class Tree(object):
    '''Creates Class tree'''
    def __init__(self, c):
        self.__root = Node()
        self.__capacity = c

    def get_root(self):
        return self.__root

    def get_leaf_threshold(self):
        return self.__capacity

    def build_tree(self, tin):
        # first we insert the vertices of the TIN
        for i in range(tin.get_vertices_num()):
            # print ("INSERT POINT %s"%tin.get_vertex(i))
            self.insert_vertex(self.__root, 0, tin.get_domain(), i,tin)
        # ADD THE CODE for inserting its triangles

        ################################################################
        # My Code

        stack = []
        stack.append(self.__root)
        node_domain = tin.get_domain()
        self.__root.set_domain(tin.get_domain())
        while len(stack) != 0:
            node = stack.pop()
            node_domain = node.get_domain()
            print(node, node_domain, "test")
            min_x = node_domain.get_min_point().get_x()
            min_y = node_domain.get_min_point().get_y()
            max_x = node_domain.get_max_point().get_x()
            max_y = node_domain.get_max_point().get_y()
            node_square = [[min_x, min_y], [max_x, min_y], [max_x, max_y], [min_x, max_y]]

            for triangle_index in range(tin.get_triangles_num()):
                triangle = tin.get_triangle(triangle_index)
                if self.is_intersecting(triangle, node_square, tin):
                    node.insert_triangle_id(triangle_index)

            if not node.is_leaf():
                for counter in range(3,-1, -1):
                    child = node.get_child(counter)
                    stack.append(child)
                    counter += 1

        stack = []
        stack.append(self.__root)
        while len(stack) != 0:
            node = stack.pop()

            for vertex_index in node.get_vertices():

                for triangle_index in range(tin.get_triangles_num()):
                    triangle = tin.get_triangle(triangle_index)

                    for curr_vertex_index in triangle.get_vertex_indices():

                        if vertex_index == curr_vertex_index:

                            node.add_incident_triangle(triangle_index)
                            # node.__incident_triangle_ids.add(triangle_index)

            if not node.is_leaf():
                for counter in range(3, -1, -1):
                    child = node.get_child(counter)
                    stack.append(child)
                    counter += 1

        ################################################################
        #  End of the build_tree() function

    def insert_vertex(self, node, node_label, node_domain, v_index, tin):
        node.set_domain(node_domain)  # My Code
        if node_domain.contains_point(tin.get_vertex(v_index),
                                      tin.get_domain().get_max_point()):
            if node.is_leaf():
                 # if the inserting vertex is the same as one vertex in tree.
                if node.is_duplicate(v_index, tin):
                    return                          # do not insert it
                node.add_vertex(v_index)  # update append list
                if node.overflow(self.__capacity):
                    # WE HAVE TO PERFORM A SPLIT OPERATION WHEN THE NUMBER OF V EXCEED CAPACITY
                    # current node become internal
                    # and we initialize its child
                    node.init_children()
                    for i in node.get_vertices():
                        self.insert_vertex(node, node_label, node_domain, i,tin)
                    node.reset_vertices()  # empty the list of the current node

            else: # otherwise we are visiting an INTERNAL node
                mid_point = node_domain.get_centroid()
                for i in range(4):
                    s_label, s_domain = node.compute_child_label_and_domain(i, node_label, node_domain,mid_point)
                    self.insert_vertex(node.get_child(i), s_label, s_domain, v_index,tin)

    def point_query(self, node, node_label, node_domain, search_point, tin):
        # node: Node object; node_label: int; node_domain: Domain object;search_point: Vertex object, the vertex you want to search
        # when point_query used in other functions for searching point:
        # node is the root of the tree,node_label is the node label of the root node(0), node_domain is the domain of the TIN(tin.get_domain()).
        # You will use this for identifying nodes containing the extreme vertices of a triangle
        #
        # This function will return the node that contains the input search_point.
        if node_domain.contains_point(search_point, tin.get_domain().get_max_point()):
            if node.is_leaf():
                isfound = False
                x = None  # x is the point id
                for i in node.get_vertices():  # for each point index in each node, if that point is equal to the query point, then it is found. Otherwise, it is not found.
                    if tin.get_vertex(i) == search_point: # here tin.get_vertex(i) and search_point are Vertex objects
                        isfound = True
                        x = i  # x is the point index that is equal to the search point.
                        print("Vertex "+str(x)+" is in Node "+str(node_label))
                        break
                if isfound:
                    return node
                else:
                    return None
            else:  # Internal node
                ### we visit the children in the following order: NW -> NE -> SW -> SE
                mid_point = node_domain.get_centroid()
                s_label, s_domain = node.compute_child_label_and_domain(0, node_label, node_domain, mid_point)
                ret_node = self.point_query(node.get_child(0), s_label, s_domain, search_point, tin)
                if ret_node is not None:
                    return ret_node
                else:
                    s_label, s_domain = node.compute_child_label_and_domain(1, node_label, node_domain, mid_point)
                    ret_node = self.point_query(node.get_child(1), s_label, s_domain, search_point, tin)
                    if ret_node is not None:
                        return ret_node
                    else:
                        s_label, s_domain = node.compute_child_label_and_domain(2, node_label, node_domain, mid_point)
                        ret_node = self.point_query(node.get_child(2), s_label, s_domain, search_point, tin)
                        if ret_node is not None:
                            return ret_node
                        else:
                            s_label, s_domain = node.compute_child_label_and_domain(3, node_label, node_domain, mid_point)
                            ret_node = self.point_query(node.get_child(3), s_label, s_domain, search_point, tin)
                            return ret_node

    def get_points(self, tin, pts):
        """return xs,ys"""
        xs = list()
        ys = list()
        for v in pts:
            xs.append(tin.get_vertex(v).get_x())
            ys.append(tin.get_vertex(v).get_y())
        return xs, ys

    def get_pts_feature_values(self,tin, fid):
        vals=list()
        for v in range(tin.get_vertices_num()):
            ver = tin.get_vertex(v)
            #print(ver, fid,ver.get_fields_num() )
            #ver.print_fields()
            if fid >= ver.get_fields_num():
                sys.exit()
            else:
                vals.append(ver.get_field(fid))
        return vals

    ################################################################
    # My Code
    def get_preorder_traversal(self, root, printLog):
        print("START TRIANGLE PR")
        self.get_preorder_traversal_helper(root, 0, printLog)
        print("END TRIANGLE PR")

    def get_preorder_traversal_helper(self, node, node_label, printLog):
        if node.is_leaf() and node.get_vertices_num() == 0:
            print(node_label, "EMPTY LEAF")

            if printLog == 1:
                print(node.get_domain())
                print("T", node.get_triangle_num(), node.get_triangle_ids())
            elif printLog == 3:
                print("VT: Relation", node.get_incident_triangle_ids())
            print("-----------------------------")
            return

        elif node.is_leaf() and node.get_vertices_num() != 0:
            print(node_label, "FULL LEAF")
            if printLog == 1:
                print(node.get_domain())
                print("V", node.get_vertices_num(), node.get_vertices())
                print("T", node.get_triangle_num(), node.get_triangle_ids())

            elif printLog == 3:
                print("VT: Relation", node.get_incident_triangle_ids())
            print("-----------------------------")
            return

        print(node_label, "INTERNAL")
        if printLog == 1:
            print(node.get_domain())
            print("T", node.get_triangle_num(), node.get_triangle_ids())
        elif printLog == 3:
            print("VT: Relation", node.get_incident_triangle_ids())
        print("-----------------------------")

        for counter in range(4):
            child = node.get_child(counter)
            self.get_preorder_traversal_helper(child, 4*node_label + (counter+1), printLog)

    def is_intersecting(self, triangle, node_square, tin):
        
        vertex_indices = triangle.get_vertex_indices()
        vertex_1 = tin.get_vertex(vertex_indices[0])
        vertex_2 = tin.get_vertex(vertex_indices[1])
        vertex_3 = tin.get_vertex(vertex_indices[2])
        triangle_perimeter = [[vertex_1.get_x(), vertex_1.get_y()],
                              [vertex_2.get_x(), vertex_2.get_y()],
                              [vertex_3.get_x(), vertex_3.get_y()]]

        print("Checking: Node Square", node_square, triangle_perimeter)
        for i in range(len(node_square)):
            square_point1 = node_square[i]
            square_point2 = node_square[(i+1) % len(node_square)]
            for j in range(len(triangle_perimeter)):
                triangle_point1 = triangle_perimeter[j]
                triangle_point2 = triangle_perimeter[(j+1) %
                                                     len(triangle_perimeter)]
                print(square_point1, square_point2,
                      triangle_point1, triangle_point2)
                if self.isIntersectingHelper(square_point1, square_point2,
                                             triangle_point1, triangle_point2):
                    print("Found intersecting!")
                    return True
        return False
    
    def isIntersectingHelper(self, p1, p2, p3, p4):

        val1 = self.getOrientation(p1, p2, p3)
        val2 = self.getOrientation(p1, p2, p4)

        val3 = self.getOrientation(p3, p4, p1)
        val4 = self.getOrientation(p3, p4, p2)

        if (val1 == 0 and val2 == 0) or (val3 == 0 and val4 == 0):
            print("Collinear")

            if (p3.x >= p1.x and p3.x <= p2.x and p3.y >= p1.y and p3.y <= p2.y):
                return True
            if (p3.x >= p1.x and p4.x <= p2.x and p4.y >= p1.y and p4.y <= p2.y):
                return True

        if (val1 != val2 and val3 != val4):
            return True
        return False

    def getOrientation(self, p1, p2, p3):

        p3p1X = p1[0] - p3[0]
        p3p1Y = p1[1] - p3[1]
        p3p2X = p2[0] - p3[0]
        p3p2Y = p2[1] - p3[1]

        determinent = (p3p1X * p3p2Y) - (p3p1Y *p3p2X)
        if (determinent > 0):
            return 1
        if (determinent < 0):
            return -1
        return 0
        ################################################################