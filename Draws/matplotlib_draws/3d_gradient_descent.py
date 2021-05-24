import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
from matplotlib.patches import FancyArrowPatch
from mpl_toolkits.mplot3d import proj3d
#from ipywidgets import interactive

'''
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

gradient = [[0,0,1,1,0,1,1,0,0,0,1,0,0,0,0,1],\
[0,1,1,1,1,0,1,0,0,0,0,0,0,0,0,1],\
[1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,1],\
[1,1,1,0,0,0,1,0,1,0,0,0,0,0,0,1],\
[1,0,0,1,0,1,0,1,0,0,0,0,0,0,0,1],\
[0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1],\
[0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1],\
[0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1],\
[0,0,0,1,1,0,2,3,3,3,2,1,1,0,0,1],\
[0,1,1,1,2,7,16,24,30,26,18,9,3,1,0,1],\
[1,1,1,4,19,41,51,52,53,54,53,50,24,6,1,1],\
[1,0,4,26,61,57,38,31,24,25,32,53,63,33,6,2],\
[1,2,21,63,51,9,7,2,4,5,3,7,42,62,31,5],\
[1,10,51,55,5,2,4,3,3,4,1,3,7,43,60,22],\
[3,30,59,24,4,2,8,3,2,7,3,3,4,8,52,43],\
[7,43,47,11,1,3,3,3,4,5,2,2,4,7,39,49]]

'''
#old border
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

class Arrow3D(FancyArrowPatch):
    def __init__(self, xs, ys, zs, *args, **kwargs):
        FancyArrowPatch.__init__(self, (0, 0), (0, 0), *args, **kwargs)
        self._verts3d = xs, ys, zs
    def draw(self, renderer):
        xs3d, ys3d, zs3d = self._verts3d
        xs, ys, zs = proj3d.proj_transform(xs3d, ys3d, zs3d, renderer.M)
        self.set_positions((xs[0], ys[0]), (xs[1], ys[1]))
        FancyArrowPatch.draw(self, renderer)


def SGN(x):
  if (x > 0):
      return 1
  if (x < 0):
      return -1

  return 0


def f(x, y, r = 6.68):    #6.41
    val = 0
    for y_p in range(0, 16):
        for x_p in range(0, 16):
            val += gradient[y_p][x_p]*abs(np.sqrt((x_p - x)**2 + (y_p - y)**2)-r)
    return val


def gradient_val(x, y, r = 6.68):   #6.41
    dx = 0
    dy = 0
    dz = 0
    for y_p in range(0, 16):
        for x_p in range(0, 16):
            x_diff = x_p - x
            y_diff = y_p - y
            x_diff_2 = x_diff**2
            y_diff_2 = y_diff**2
            if ((x_diff_2 + y_diff_2) == 0):
                continue
              
            dx += gradient[y_p][x_p] * SGN(np.sqrt(x_diff_2 + y_diff_2) - r) * x_diff / np.sqrt(x_diff_2 + y_diff_2)
            dy += gradient[y_p][x_p] * SGN(np.sqrt(x_diff_2 + y_diff_2) - r) * y_diff / np.sqrt(x_diff_2 + y_diff_2)
#            dz += gradient[y_p][x_p] * SGN(np.sqrt(x_diff_2 + y_diff_2) - r)
    return (dx, dy)


    
x = np.linspace(3, 13, 1000)
y = np.linspace(3, 18, 1000)
#x = np.linspace(0, 16, 1000)
#y = np.linspace(0, 16, 1000)
X, Y = np.meshgrid(x, y)
Z = f(X, Y)

fig = plt.figure(figsize = [12, 8])
ax = fig.gca(projection = '3d')
Z = f(X, Y)

'''
x_grad = 14
y_grad = 14
K = 1000
components = gradient_val(x_grad, y_grad)
#components = (3, 3, 10000)
print(components)
a = Arrow3D([x_grad, x_grad+components[0]/K], [y_grad, y_grad+components[1]/K], [Z[round(x_grad*1000/16)][round(y_grad*1000/16)], Z[round(x_grad*1000/16)][round(y_grad*1000/16)]], mutation_scale=20, lw=10, arrowstyle="-|>", color="k")
ax.add_artist(a)
'''

ax.plot_surface(X, Y, Z, cmap=cm.coolwarm_r)

plt.show()
