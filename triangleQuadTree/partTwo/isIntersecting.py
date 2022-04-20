# # def is_intersecting(triangle, node_square, tin):
# def is_intersecting(node_square):

#     square_min_x = node_square[0][0]
#     square_min_y = node_square[0][1]
#     square_max_x = node_square[3][0]
#     square_max_y = node_square[3][1]

#     # triangle.
#     # vertex_indices = triangle.get_vertex_indices()
#     # vertex_1 = tin.get_vertex(vertex_indices[0])
#     # vertex_2 = tin.get_vertex(vertex_indices[1])
#     # vertex_3 = tin.get_vertex(vertex_indices[2])

#     # triangle_perimeter = [[vertex_1.get_x(), vertex_1.get_y()],[vertex_2.get_x(), vertex_2.get_y()],[vertex_3.get_x(), vertex_3.get_y()]] 
#     triangle_perimeter = [[200,200],[300,300],[22, 400]] 


#     triangle_min_x = 0
#     triangle_min_y = 0
#     triangle_max_x = 0
#     triangle_max_y = 0

#     print(node_square)
#     print(triangle_perimeter)

#     print(square_min_x, square_min_y)
#     print(square_max_x, square_max_y)
#     for triangle_point in triangle_perimeter:
#         triangle_x =  triangle_point[0]
#         triangle_y =  triangle_point[1]
#         print(triangle_point)
#         if (square_max_x >= triangle_x >= square_min_x and square_max_y >= triangle_y >= square_min_y ):
#             print("Intersected -1")
#             return True
        
#         if ( triangle_x > triangle_max_x):
#             triangle_max_x = triangle_x
        
#         if ( triangle_y > triangle_max_y):
#             triangle_max_y = triangle_y

#         if ( triangle_x < triangle_min_x):
#             triangle_min_x = triangle_x
        
#         if ( triangle_y < triangle_min_y):
#             triangle_min_y = triangle_y
        
#     print(triangle_min_x, triangle_min_y)
#     print(triangle_max_x, triangle_max_y)

#     for square_point in node_square:
#         square_x =  square_point[0]
#         square_y =  square_point[1]
#         print(square_point)
#         if (triangle_max_x >= square_x >= triangle_min_x and triangle_max_y >= square_y >= triangle_min_y):
#             print("Intersected -2")
#             return True
#     print("No intersection!!!!!!!!")
#     return False


def is_intersecting(node_square):

    triangle_perimeter = [[400,400],[300,300],[22, 400]] 

    # val1 = getOrientation((vertex_1.get_x(), vertex_1.get_y()),vertex_2.get_x(), vertex_2.get_y()),node_square[0])
    # val2 = getOrientation((vertex_2.get_x(), vertex_2.get_y()),vertex_3.get_x(), vertex_3.get_y()),node_square[1])
    # val3 = getOrientation((vertex_3.get_x(), vertex_3.get_y()),vertex_1.get_x(), vertex_1.get_y()),node_square[0])

    val1 = getOrientation([triangle_perimeter[0][0], triangle_perimeter[0][1]],[triangle_perimeter[1][0], triangle_perimeter[1][1]],node_square[0])
    val2 = getOrientation([triangle_perimeter[1][0], triangle_perimeter[1][1]],[triangle_perimeter[2][0], triangle_perimeter[2][1]],node_square[0])
    val3 = getOrientation([triangle_perimeter[2][0], triangle_perimeter[2][1]],[triangle_perimeter[0][0], triangle_perimeter[0][1]],node_square[0])

    p1 = triangle_perimeter[0]
    p2 = triangle_perimeter[1]
    p3 = triangle_perimeter[0]


    if ( val1 != val2 or val2 != val3 or val3 != val1):
        return False
    return True

def getOrientation(p1, p2, p3):

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

print(is_intersecting([[22,20],[22,400],[400,400], [22,400]]))

















def is_intersecting(self, triangle, node_square, tin):

    square_min_x = node_square[0][0]
    square_min_y = node_square[0][1]
    square_max_x = node_square[3][0]
    square_max_y = node_square[3][1]

    # triangle.
    vertex_indices = triangle.get_vertex_indices()
    vertex_1 = tin.get_vertex(vertex_indices[0])
    vertex_2 = tin.get_vertex(vertex_indices[1])
    vertex_3 = tin.get_vertex(vertex_indices[2])

    triangle_perimeter = [[vertex_1.get_x(), vertex_1.get_y()],[vertex_2.get_x(), vertex_2.get_y()],[vertex_3.get_x(), vertex_3.get_y()]] 

    print("Checking intersection between", triangle_perimeter, node_square)
    triangle_min_x = vertex_1.get_x()
    triangle_min_y = vertex_1.get_y()
    triangle_max_x = vertex_1.get_x()
    triangle_max_y = vertex_1.get_y()

    for triangle_point in triangle_perimeter:
        triangle_x =  triangle_point[0]
        triangle_y =  triangle_point[1]
        if (square_max_x >= triangle_x >= square_min_x and square_max_y >= triangle_y >= square_min_y ):
            print("Intersected -1")
            return True
        
        if ( triangle_x > triangle_max_x):
            triangle_max_x = triangle_x
        
        if ( triangle_y > triangle_max_y):
            triangle_max_y = triangle_y

        if ( triangle_x < triangle_min_x):
            triangle_min_x = triangle_x
        
        if ( triangle_y < triangle_min_y):
            triangle_min_y = triangle_y
        
    for square_point in node_square:
        square_x =  square_point[0]
        square_y =  square_point[1]
        if (triangle_max_x >= square_x >= triangle_min_x and triangle_max_y >= square_y >= triangle_min_y):
            print("Intersected -2")
            return True
    print("No intersection!!!!!!!!")
    return False