import numpy as np
import cext04

print('A new array from C extention')
a = cext04.as_nparray()
print(a)

print('Reading array b in C extension')
b = np.ones((4, 3))
cext04.read_2darray(b)
