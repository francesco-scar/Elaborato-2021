import matplotlib.pyplot as plt
import numpy as np

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

x = -0.53 + 7.5
y = 1.11 + 7.5

def f(r):
    val = 0
    for y_p in range(0, 16):
        for x_p in range(0, 16):
            val += gradient[y_p][x_p]*abs(np.sqrt((x_p - x)**2 + (y_p - y)**2)-r)
    return val

X = np.linspace(0, 16, 1000)
Y = f(X)

plt.plot(X, Y)
plt.show()
