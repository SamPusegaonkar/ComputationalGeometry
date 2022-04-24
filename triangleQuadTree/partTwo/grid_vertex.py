class GridVertex:

    def __init__(self, x_, y_):
        self.x = x_
        self.y = y_
        self.z = float('nan')
        self.triangles_indices = set()
