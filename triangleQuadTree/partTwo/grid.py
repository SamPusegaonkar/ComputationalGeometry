
import numpy as np
import math

from reader import Reader
from grid_vertex import GridVertex


class Grid:

    def __init__(self, starting_x, starting_y,
                 cell_height, cell_width,
                 n_rows, n_cols):

        self.starting_x = starting_x
        self.starting_y = starting_y
        self.cell_wdith = cell_width
        self.cell_height = cell_height
        self.n_cols = n_cols
        self.n_rows = n_rows
        self.grid = [[GridVertex(i*cell_height + self.starting_x, j*cell_width + self.starting_y) for j in range(n_cols+1)] for i in range(n_rows+1, -1, -1)]

    def getElevationAt(self, row, col):
        pass

    def getElevations(self):

        # file_name = input("Enter the file name of tin")
        self.getIntersectingTriangles( 'pts-dt.off')

    def isOnTriangleVertex(self, tin, grid_vertex, index):
        print("checking if point is on vertex")
        triangle = tin.get_triangle(index)
        for vertex_index in triangle.get_vertex_indices():
            vertex = tin.get_vertex(vertex_index)
            if self.isEqual(vertex.get_x(), vertex.get_y(), grid_vertex.x, grid_vertex.y):
                print("Point is on triangle vertex", grid_vertex.x, grid_vertex.y)
                return True, vertex.get_z()
        print("Point is not on vertex")
        return False, 0.0

    def isEqual(self, x, y, grid_x, grid_y):

        if (abs(x - grid_x) <= 0.0001 and abs(y - grid_y) <= 0.0001):
            return True
        return False

    def isPointInsideTriangle(self, i, j, triangle, tin):

        vertex_indices = triangle.get_vertex_indices()
        vertex_1 = tin.get_vertex(vertex_indices[0])
        vertex_2 = tin.get_vertex(vertex_indices[1])
        vertex_3 = tin.get_vertex(vertex_indices[2])

        val1 = self.getOrientation([vertex_1.get_x(), vertex_1.get_y()], [vertex_2.get_x(), vertex_2.get_y()], [i, j])
        val2 = self.getOrientation([vertex_2.get_x(), vertex_2.get_y()], [vertex_3.get_x(), vertex_3.get_y()], [i, j])
        val3 = self.getOrientation([vertex_3.get_x(), vertex_3.get_y()], [vertex_1.get_x(), vertex_1.get_y()], [i, j])
        print([vertex_1.get_x(), vertex_1.get_y()], [vertex_2.get_x(), vertex_2.get_y()], [vertex_3.get_x(), vertex_3.get_y()])

        print(val1, val2, val3)

        has_neg = (val1 < 0) or (val2 < 0) or (val3 < 0)
        has_pos = (val1 > 0) or (val2 > 0) or (val3 > 0)
        return not (has_neg and has_pos)

    def getIntersectingVertices(self, tin, grid_vertex):

        for triangle_index in grid_vertex.triangles_indices:
            triangle = tin.get_triangle(triangle_index)
            vertex_indices = triangle.get_vertex_indices()

            vertex_1 = tin.get_vertex(vertex_indices[0])
            vertex_2 = tin.get_vertex(vertex_indices[1])
            vertex_3 = tin.get_vertex(vertex_indices[2])

            if (self.isPointOnEdgeHelper(vertex_1, vertex_2, grid_vertex)):
                return [vertex_1, vertex_2]

            if (self.isPointOnEdgeHelper(vertex_2, vertex_3, grid_vertex)):
                return [vertex_1, vertex_2]

            if (self.isPointOnEdgeHelper(vertex_3, vertex_1, grid_vertex)):
                return [vertex_1, vertex_2]
        return []

    def isPointOnEdgeHelper(self, vertex_1, vertex_2, grid_vertex):

        x1 = vertex_1.get_x()
        y1 = vertex_1.get_y()
        p1 = [x1, y1]

        x2 = vertex_2.get_x()
        y2 = vertex_2.get_y()
        p2 = [x2, y2]

        x4 = grid_vertex.x
        y4 = grid_vertex.y
        p3 = [x4, y4]

        # Collinear
        if self.getOrientation(p1, p2, p3) == 0:
            if p2[0] >= p3[0] >= p1[0] and p2[1] >= p3[1] >= p1[1] :
                return True
            elif p1[0] >= p3[0] >= p2[0] and p1[1] >= p3[1] >= p2[1]:
                return True
        return False

    def setZElevation(self, vertices, grid_vertex):
        
        vertex_1, vertex_2 = vertices
        x1 = vertex_1.get_x()
        y1 = vertex_1.get_y()
        z1 = vertex_1.get_z()
        p1 = [x1, y1, z1]

        x2 = vertex_2.get_x()
        y2 = vertex_2.get_y()
        z2 = vertex_2.get_z()
        p2 = [x2, y2, z2]

        x4 = grid_vertex.x
        y4 = grid_vertex.y
        p3 = [x4, y4]

        d = self.getEuclidianDistance(p1, p3)
        v = [p2[0] - p1[0], p2[1] - p1[1], p2[2] - p1[2]]
        mag_v = self.getMagnitude(v)
        multiplier = d/mag_v
        grid_vertex.z = p1[2] + multiplier * v[2]
        return None

    def getEuclidianDistance(self, p1, p2):
        return math.sqrt((p1[0] - p2[0])**2 + (p1[1]-p2[1])**2)

    def getMagnitude(self, x):
        return math.sqrt(x[0] * x[0] + x[1]*x[1] + x[2]*x[2])

    def getOrientation(self, p1, p2, p3):

        p3p1X = p1[0] - p3[0]
        p3p1Y = p1[1] - p3[1]
        p3p2X = p2[0] - p3[0]
        p3p2Y = p2[1] - p3[1]

        determinent = (p3p1X * p3p2Y) - (p3p1Y * p3p2X)
        return determinent

    def getIntersectingTriangles(self, file_name):

        reader = Reader()
        tin = reader.read_tin_file("pts-dt.off")

        for i in range(len(g.grid)):
            for j in range(len(g.grid[0])):
                print("-----------------------------------")
                grid_vertex = self.grid[i][j]
                print(grid_vertex.x, grid_vertex.y, "x and y")
                for triangle_index in range(tin.get_triangles_num()):
                    triangle = tin.get_triangle(triangle_index)

                    onVertex, z_elevation = self.isOnTriangleVertex(tin, grid_vertex, triangle_index)
                    if onVertex:
                        grid_vertex.z = z_elevation
                        break

                    if (self.isPointInsideTriangle(grid_vertex.x, grid_vertex.y, triangle, tin)): 
                        print("Point is inside TIN")       
                        print(i, j, triangle)              
                        grid_vertex.triangles_indices.add(triangle_index)
                        print("==========")
                    else:
                        print("point not inside tin")
                    print("``````````````````````````````````````")


                # If the point is on an edge
                vertices = self.getIntersectingVertices(tin, grid_vertex)
                if len(vertices): 
                    print("found", len(vertices))
                    self.setZElevation(vertices, grid_vertex)
                    print(grid_vertex.z)

                else:
                    grid_vertex.z = self.getElevationHelper(grid_vertex, tin)
    
    def getElevationHelper(self, grid_vertex, tin):
        
        print(grid_vertex.triangles_indices)

        print(len(grid_vertex.triangles_indices))
        
        for triangle_index in grid_vertex.triangles_indices:
            triangle = tin.get_triangle(triangle_index)
            vertex_indices = triangle.get_vertex_indices()

            vertex_1 = tin.get_vertex(vertex_indices[0])
            vertex_2 = tin.get_vertex(vertex_indices[1])
            vertex_3 = tin.get_vertex(vertex_indices[2])

            x1 = vertex_1.get_x()
            y1 = vertex_1.get_y()
            z1 = vertex_1.get_z()

            x2 = vertex_2.get_x()
            y2 = vertex_2.get_y()
            z2 = vertex_2.get_z()

            x3 = vertex_3.get_x()
            y3 = vertex_3.get_y()
            z3 = vertex_3.get_z()

            x4 = grid_vertex.x
            y4 = grid_vertex.y

            p1 = [x1, y1, z1]
            p2 = [x2, y2, z2]
            p3 = [x3, y3, z3]

            P = p1
            N = np.cross(np.subtract(p2, P), np.subtract(p3, P))
            z4 = z1 - ((x4-x1)*N[0] + (y4-y1)*N[1]) / N[2]
            return z4

    def printAllElevations(self):

        with open("grid.txt", "w") as file1:
            file1.write("The output is in a grid format!\n")
            file1.write("Format: (x,y,z) where x,y,z are the coordinates of the grid\n\n")

            print("The output is in a grid format!")
            print("Format: (x,y,z) where x,y,z are the coordinates of the grid\n")

            for i in range(len(self.grid)):
                for j in range(len(self.grid[0])):
                    curr_output = "(" + str(self.grid[i][j].x) + " " + \
                                  str(self.grid[i][j].y) + " " + str(self.grid[i][j].z) + "), "

                    print(curr_output)
                    file1.write(curr_output) 
                file1.write("\n")
                print('\n')
