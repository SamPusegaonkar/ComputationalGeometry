
class Triangle(object):
    """ A Triangle is encoded as the triple of the indexes of its vertices in the Vertex array"""

    ################################################################
    #My Code
    def __init__(self, vertex_index_1, vertex_index_2, vertex_index_3):
        self.vertex_indices = list()
        self.vertex_indices.append(vertex_index_1)
        self.vertex_indices.append(vertex_index_2)
        self.vertex_indices.append(vertex_index_3)
    ################################################################
