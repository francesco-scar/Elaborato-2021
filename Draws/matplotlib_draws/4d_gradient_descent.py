import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
#from ipywidgets import interactive


gradient = [[1,1,0,0,0,0,1,1,0,1,3,3,3,3,3,4,],\
[0,1,1,1,2,7,14,18,15,7,1,2,2,2,2,3,],\
[1,0,2,7,28,40,40,38,41,40,28,7,2,1,1,1,],\
[2,1,11,44,49,34,24,21,24,33,48,43,12,1,1,0,],\
[1,9,49,45,12,2,1,1,1,1,11,41,48,12,1,1,],\
[3,40,45,4,1,1,2,1,1,1,0,3,41,40,6,1,],\
[20,48,16,1,1,1,1,2,1,0,1,1,16,45,21,1,],\
[35,38,3,1,1,0,0,1,3,1,1,0,3,38,33,3,],\
[37,31,1,0,1,1,0,1,1,2,1,1,0,31,38,7,],\
[37,30,1,0,1,1,1,0,3,2,0,0,0,31,38,7,],\
[36,32,1,0,0,0,1,1,1,2,1,0,2,36,36,5,],\
[29,42,6,0,1,0,0,1,1,1,1,1,11,45,27,2,],\
[12,46,26,3,0,1,1,1,1,1,0,2,34,45,11,1,],\
[1,26,50,29,1,1,0,1,1,2,2,29,51,21,3,1,],\
[1,1,26,49,41,19,11,9,12,22,40,50,23,3,1,1,],\
[1,1,1,11,40,42,37,36,38,43,37,15,2,2,1,1]]
'''
gradient = [[1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,1,],\
[1,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,],\
[1,0,0,1,1,1,1,1,1,1,0,0,0,1,1,0,],\
[0,0,1,1,1,0,0,0,0,1,1,0,0,1,1,0,],\
[1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,],\
[1,1,0,0,0,0,0,1,1,0,0,0,1,1,0,0,],\
[0,0,0,0,1,0,1,1,0,0,0,1,1,1,0,0,],\
[1,0,1,1,0,2,0,1,1,0,1,1,0,1,0,1,],\
[0,1,1,1,0,1,2,1,1,1,1,1,0,1,0,1,],\
[1,1,1,0,1,3,10,14,17,13,5,3,1,1,1,1,],\
[0,1,1,2,10,35,52,54,52,54,48,27,6,1,0,1,],\
[1,1,2,18,57,62,47,35,33,38,56,68,49,10,2,1,],\
[1,1,19,62,52,16,2,4,2,6,7,26,65,55,10,1,],\
[1,11,53,54,7,2,5,4,6,2,2,4,17,64,45,5,],\
[2,33,65,19,7,4,2,5,2,3,2,1,3,32,65,26,],\
[6,50,50,6,0,4,2,1,5,2,1,4,3,7,55,44]]
'''

def f(x, y, r):
    val = 0
    for y_p in range(0, 16):
        for x_p in range(0, 16):
            val += gradient[y_p][x_p]*abs(np.sqrt((x_p - x)**2 + (y_p - y)**2)-r)
    return val

def map_color(val):
    color = cm.coolwarm_r(val/max_val)
    return '#%02x%02x%02x' % (round(color[0]*255), round(color[1]*255), round(color[2]*255))

x = np.linspace(0, 16, 8)
y = np.linspace(0, 16, 8)
z = np.linspace(0, 16, 8)
X, Y, Z = np.meshgrid(x, y, z)
W = f(X, Y, Z)

max_val = 0

for i in range(len(X)):
    for j in range(len(X[0])):
        for k in range(len(X[0][0])):
            if W[i][j][k] > max_val:
                max_val = W[i][j][k]
                
#color_map = [[[0]*10]*10]*10
color_map = [[], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], []]
'''
for i in range(len(X)):
    for j in range(len(X[0])):
        for k in range(len(X[0][0])):
#            color_map[i][j][k] = map_color(W[i][j][k])
            color_map.append(map_color(W[i][j][k]))
'''
for i in range(len(X)):
    for j in range(len(X[0])):
        for k in range(len(X[0][0])):
            color_map[i].append(map_color(W[i][j][k]))

fig = plt.figure()
ax = fig.gca(projection = '3d')

'''
for i in range(len(X)):
    for j in range(len(X[0])):
        for k in range(len(X[0][0])):
            ax.scatter(X[i][j][k], Y[i][j][k], Z[i][j][k], color=map_color(W[i][j][k]))
'''

for i in range(len(X)):
    ax.scatter(X[i], Y[i], Z[i], c=color_map[i])

#plt.scatter(X, Y, Z, W, cmap="gray")
plt.show()

