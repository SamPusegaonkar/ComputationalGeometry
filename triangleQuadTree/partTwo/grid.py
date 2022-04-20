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
        self.grid = [[GridVertex(i*cell_height + self.starting_x, j*cell_width + self.starting_y)  for j in range(n_cols+1)] for i in range(n_rows+1)]


    def getElevationAt(self, row, col):
        pass

    def getElevations(self):
        
        # file_name = input("Enter the file name of tin")
        self.getIntersectingTriangles( 'pts-dt.off')

    def isOnTriangleVertex(self, tin, grid_vertex):

        for index in grid_vertex.triangles_indices:
            triangle = tin.get_triangle(index)
            for vertex_index in triangle.get_vertex_indices():
                vertex = tin.get_vertex(vertex_index)
                if self.isEqual(vertex.get_x(), vertex.get_y(), grid_vertex.x, grid_vertex.y):
                    return True, vertex.get_z()
        return False

    def isEqual(self, x, y, grid_x, grid_y):
        if ( abs(x - grid_x) < 0.0001 and abs(y - grid_y) < 0.0001):
            return True
        return False

    def isPointInsideTriangle(self, i, j, triangle, tin):

        vertex_indices = triangle.get_vertex_indices()
        vertex_1 = tin.get_vertex(vertex_indices[0])
        vertex_2 = tin.get_vertex(vertex_indices[1])
        vertex_3 = tin.get_vertex(vertex_indices[2])
        
        val1 = self.getOrientation((vertex_1.get_x(), vertex_1.get_y()),(vertex_2.get_x(), vertex_2.get_y()),[i,j])
        val2 = self.getOrientation((vertex_2.get_x(), vertex_2.get_y()),(vertex_3.get_x(), vertex_3.get_y()),[i,j])
        val3 = self.getOrientation((vertex_3.get_x(), vertex_3.get_y()),(vertex_1.get_x(), vertex_1.get_y()),[i,j])


        if ( val1 != val2 or val2 != val3 or val3 != val1):
            return False
        return True
    
    def getOrientation(self, p1, p2, p3):

        p3p1X = p1[0] - p3[0]
        p3p1Y = p1[1] - p3[1]
        p3p2X = p2[0] - p3[0]
        p3p2Y = p2[1] - p3[1]

        determinent = (p3p1X * p3p2Y ) - (p3p1Y *p3p2X )
        if (determinent > 0):
            return 1
        if (determinent < 0):
            return -1
        return 0



    def getIntersectingTriangles(self, file_name):

        reader = Reader()
        tin = reader.read_tin_file("pts-dt.off")

        for i in range(len(g.grid)):
            for j in range(len(g.grid[0])):
                grid_vertex = self.grid[i][j]
                for triangle_index in range(tin.get_triangles_num()):
                    triangle = tin.get_triangle(triangle_index)
                    if ( self.isPointInsideTriangle(i, j, triangle, tin)):
                        
                        grid_vertex.triangles_indices.add(triangle_index)
                        onVertex, z_elevation = self.isOnTriangleVertex(tin, grid_vertex)
                        if onVertex:
                            self.z = z_elevation
                # onEdge, z_elevation = grid_vertex.isOnTriangleEdge(tin)
                onEdge = False
                if ( onEdge):
                    #use 2 sides to interpolate
                    pass
                else:
                    grid_vertex.z = float("inf")
                

g = Grid(0,0,10,10,10,10)
g.getElevations()

for i in range(len(g.grid)):
    for j in range(len(g.grid[0])):
        print(g.grid[i][j].x, g.grid[i][j].y, g.grid[i][j].z, end = ",")

    print("\n")