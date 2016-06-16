import numpy as np
import cext08

print('A new array from C extention')
a = cext08.as_nparray()
print(a)

