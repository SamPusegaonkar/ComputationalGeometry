import numpy as np
x1 = 0
y1 = 0
z1 = 0

x2 = 10
y2 = 10
z2 = 0

x3 = 10
y3 = 0
z3 = 0

x4 = 9
y4 = 1

p1 = [ x1, y1, z1]
p2 = [ x2, y2, z2]
p3 = [ x3, y3, z3]

P = p1

print(np.subtract(p2,P))
print(np.subtract(p3,P))


N = np.cross(np.subtract(p2,P), np.subtract(p3,P))
print(N)


z4 = z1 - ((x4-x1)*N[0] + (y4-y1)*N[1])/ N[2]
print(z4, "here")

