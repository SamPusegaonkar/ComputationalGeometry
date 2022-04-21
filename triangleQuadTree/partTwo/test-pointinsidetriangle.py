def isPointInsideTriangle(self, i, j, triangle, tin):

    vertex_indices = triangle.get_vertex_indices()
    vertex_1 = tin.get_vertex(vertex_indices[0])
    vertex_2 = tin.get_vertex(vertex_indices[1])
    vertex_3 = tin.get_vertex(vertex_indices[2])
    
    points = self.sortPoints([[vertex_1.get_x(), vertex_1.get_y()], [vertex_2.get_x(), vertex_2.get_y()], [vertex_3.get_x(), vertex_3.get_y()]])
    vertex_1 = points[0]
    vertex_2 = points[1]
    vertex_3 = points[2]

    print(points)
    val1 = self.getOrientation([vertex_1[0], vertex_1[1]],[vertex_2[0], vertex_2[1]],[i,j])
    val2 = self.getOrientation([vertex_2[0], vertex_2[1]],[vertex_3[0], vertex_3[1]],[i,j])
    val3 = self.getOrientation([vertex_1[0], vertex_1[1]],[vertex_3[0], vertex_3[1]],[i,j])
    print(val1, val2, val3)

    has_neg = (val1 < 0) or (val2 < 0) or (val3 < 0)
    has_pos = (val1 > 0) or (val2 > 0) or (val3 > 0)
    return not (has_neg and has_pos)

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