
import numpy as np
import math

from reader import Reader
from grid_vertex import GridVertex

class Grid:

    def __init__(self, starting_x, starting_y, cell_height, cell_width, n_rows, n_cols):
        self.starting_x = starting_x
        self.starting_y = starting_y
        self.cell_wdith = cell_width
        self.cell_height = cell_height
        self.n_cols = n_cols
        self.n_rows = n_rows
        self.grid = [[GridVertex(i*cell_height + self.starting_x, j*cell_width + self.starting_y)  for j in range(n_cols+1)] for i in range(n_rows+1,-1, -1)]


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

        if ( abs(x - grid_x) <= 0.0001 and abs(y - grid_y) <= 0.0001):
            return True
        return False

    def isEqual(self, a, b):
        return abs(a-b) <= 0.0001


    def isPointInsideTriangle(self, i, j, triangle, tin):

        vertex_indices = triangle.get_vertex_indices()
        vertex_1 = tin.get_vertex(vertex_indices[0])
        vertex_2 = tin.get_vertex(vertex_indices[1])
        vertex_3 = tin.get_vertex(vertex_indices[2])
        
        # # points = self.sortPoints([[vertex_1.get_x(), vertex_1.get_y()], [vertex_2.get_x(), vertex_2.get_y()], [vertex_3.get_x(), vertex_3.get_y()]])
        # vertex_1 = points[0]
        # vertex_2 = points[1]
        # vertex_3 = points[2]

        # print(points)
        # val1 = self.getOrientation([vertex_1[0], vertex_1[1]],[vertex_2[0], vertex_2[1]],[i,j])
        # val2 = self.getOrientation([vertex_2[0], vertex_2[1]],[vertex_3[0], vertex_3[1]],[i,j])
        # val3 = self.getOrientation([vertex_3[0], vertex_3[1]],[vertex_1[0], vertex_1[1]],[i,j])


        # val1 = self.getOrientation([vertex_1.get_x(), vertex_1.get_y()],[vertex_2.get_x(), vertex_2.get_y()],[i,j])
        # val2 = self.getOrientation([vertex_2.get_x(), vertex_2.get_y()],[vertex_3.get_x(), vertex_3.get_y()],[i,j])
        # val3 = self.getOrientation([vertex_3.get_x(), vertex_3.get_y()],[vertex_1.get_x(), vertex_1.get_y()],[i,j])
        print([vertex_1.get_x(), vertex_1.get_y()], [vertex_2.get_x(), vertex_2.get_y()], [vertex_3.get_x(), vertex_3.get_y()])

        # # print(val1, val2, val3)

        # has_neg = (val1 < 0) or (val2 < 0) or (val3 < 0)
        # has_pos = (val1 > 0) or (val2 > 0) or (val3 > 0)
        # return not (has_neg and has_pos)
        p = [i,j]
        p0 = [vertex_1.get_x(), vertex_1.get_y()]
        p1 = [vertex_2.get_x(), vertex_2.get_y()]
        p2 = [vertex_3.get_x(), vertex_3.get_y()]

        return self.isPointInsideTriangleHelper(p, p0, p1, p2)
    
    def isPointInsideTriangleHelper(self, p, p0, p1, p2):
        s = (p0[0] - p2[0]) * (p[1] - p2[1]) - (p0[1] - p2[1]) * (p[0] - p2[0])
        t = (p1[0] - p0[0]) * (p[1] - p0[1]) - (p1[1] - p0[1]) * (p[0] - p0[0])

        if ((s < 0) != (t < 0) and s != 0 and t != 0):
            return False

        d = (p2[0] - p1[0]) * (p[1] - p1[1]) - (p2[1] - p1[1]) * (p[0] - p1[0])
        print(d)
        return d == 0 or (d < 0) == (s + t <= 0)

    def getOrientation(self, p1, p2, p3):

        p3p1X = p1[0] - p3[0]
        p3p1Y = p1[1] - p3[1]
        p3p2X = p2[0] - p3[0]
        p3p2Y = p2[1] - p3[1]

        determinent = (p3p1X * p3p2Y ) - (p3p1Y *p3p2X )
        return determinent


    def sortPoints(self, points):
        return sorted(points, key=key)


    def getIntersectingTriangles(self, file_name):

        reader = Reader()
        tin = reader.read_tin_file("pts-dt.off")

        for i in range(len(g.grid)):
            for j in range(len(g.grid[0])):
                print("-----------------------------------")
                grid_vertex = self.grid[i][j]
                print(grid_vertex.x , grid_vertex.y, "x and y")
                for triangle_index in range(tin.get_triangles_num()):
                    triangle = tin.get_triangle(triangle_index)
                    
                    onVertex, z_elevation = self.isOnTriangleVertex(tin, grid_vertex, triangle_index)
                    if onVertex:
                        grid_vertex.z = z_elevation
                        break
                        
                    if ( self.isPointInsideTriangle(i, j, triangle, tin)):   
                        print("Point is inside TIN")       
                        print(i, j, triangle)              
                        grid_vertex.triangles_indices.add(triangle_index)
                        print("==========")
                    else:
                        print("point not inside tin")
                        

                # onEdge, z_elevation = self.isOnEdge(tin, grid_vertex)
                onEdge, z_elevation = False, 0.0
                if (onEdge):
                    grid_vertex.z = z_elevation
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

            p1 = [ x1, y1, z1]
            p2 = [ x2, y2, z2]
            p3 = [ x3, y3, z3]

            P = p1
            N = np.cross(np.subtract(p2,P), np.subtract(p3,P))
            z4 = z1 - ((x4-x1)*N[0] + (y4-y1)*N[1])/ N[2]
            return z4

def key(x):
    atan = math.atan2(x[1], x[0])
    return (atan, x[1]**2+x[0]**2) if atan >= 0 else (2*math.pi + atan, x[0]**2+x[1]**2)

#starting point x, y, grid cell size (height and width), number of rows, and number of cols.
g = Grid(45,45,20,20,2,2)
g.getElevations()

for i in range(len(g.grid)):
    for j in range(len(g.grid[0])):
        print(g.grid[i][j].x, g.grid[i][j].y, g.grid[i][j].z, end = ",")
    print("\n")