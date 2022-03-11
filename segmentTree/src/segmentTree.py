import math

class Point:
    def __init__(self, _x, _y):
        self.x = _x
        self.y = _y

# def merge(num1, num2):
#     return num1 + num2

def getEuclidianDistance(point1):
    return math.sqrt((point1.x - 0)**2 + (point1.y - 0)**2)

def merge(point1, point2):
    
    euclidianDistance1 = getEuclidianDistance(point1)
    euclidianDistance2 = getEuclidianDistance(point2)
    if ( euclidianDistance1 > euclidianDistance2):
        return point2
    return point1

def buildTree(arr, low, high, treeIndex):

    #Base
    if ( low == high ):
        tree[treeIndex] = arr[low]
        return


    #Logic
    mid = (low) + (high - low) //2
    buildTree(arr, low, mid, 2*treeIndex+1)
    buildTree(arr, mid+1, high, 2*treeIndex+2)
    tree[treeIndex] = merge(tree[2*treeIndex +1], tree[2*treeIndex +2])

def findInRange(i,j, low, high, treeIndex):

    #basebuildTree
    if ( low > j or high < i):
        return None

    if ( i <= low and j >= high):
        return tree[treeIndex]

    #logic
    mid = low + (high - low)//2
    if ( i > mid ):
        return findInRange(i,j,mid+1,high, 2*treeIndex + 2)
    elif ( j <= mid):
        return findInRange(i,j,low,mid, 2*treeIndex + 1)
    leftQuery = findInRange(i, j, low, mid, 2*treeIndex + 1)
    rightQuery = findInRange(i, j, mid +1, high, 2*treeIndex + 2)

    return merge(leftQuery, rightQuery)

# arr = [10,20,100,12,11,12,5,6,7]
# tree = [0] * 4*len(arr)
# buildTree(arr, 0, len(arr)-1, 0)
# print(arr)
# print(tree)
# print(findInRange(0, 5, 0, len(arr), 0))

arr = [Point(10,10), Point(20,10), Point(30,10), Point(0,0), Point(10,10), Point(40,10)]
tree = [0] * 4*len(arr)
buildTree(arr, 0, len(arr)-1, 0)
for arrPoint in arr:
    print(arrPoint.x, arrPoint.y)
print("Nearest Point")
nearestPoint = findInRange(0, len(arr), 0, len(arr), 0)
print(nearestPoint.x, nearestPoint.y)