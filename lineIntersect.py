
class Point:
    def __init__(self, _x, _y):
        self.x = _x
        self.y = _y

#Getting the orientation of point p3 wrt p1p2.
def getOrientation(p1, p2, p3):

    p3p1X = p1.x - p3.x
    p3p1Y = p1.y - p3.y
    p3p2X = p2.x - p3.x
    p3p2Y = p2.y - p3.y

    determinent = (p3p1X * p3p2Y ) - (p3p1Y *p3p2X )
    if (determinent > 0):
        return 1
    if (determinent < 0):
        return -1
    return 0


def isIntersecting(p1, p2, p3, p4):

    val1 = getOrientation(p1,p2,p3)
    val2 = getOrientation(p1,p2,p4)

    val3 = getOrientation(p3,p4,p1)
    val4 = getOrientation(p3,p4,p2)

    if ( (val1 == 0 and val2 == 0) or (val3 == 0 and val4 == 0)):
        print("Collinear")

        if ( p3.x >= p1.x and p3.x <= p2.x and  p3.y >= p1.y and p3.y <= p2.y):
            return True
        if ( p3.x >= p1.x and p4.x <= p2.x and  p4.y >= p1.y and p4.y <= p2.y):
            return True

    if ( val1 != val2 and val3 != val4):
        return True
    return False
    


p1 = Point(10,10)
p2 = Point(20,20)
p3 = Point(10,20)
p4 = Point(20,10)

print(isIntersecting(p1,p2,p3,p4))
print("-----------------------------")

p1 = Point(10,10)
p2 = Point(20,20)
p3 = Point(20,20)
p4 = Point(40,40)

print(isIntersecting(p1,p2,p3,p4))
print("-----------------------------")

p1 = Point(10,10)
p2 = Point(20,20)
p3 = Point(30,30)
p4 = Point(40,40)

print(isIntersecting(p1,p2,p3,p4))
print("-----------------------------")
p1 = Point(-5,-5)
p2 = Point(0,0)
p3 = Point(1,1)
p4 = Point(10,10)

print(isIntersecting(p1,p2,p3,p4))
print("-----------------------------")
