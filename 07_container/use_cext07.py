import numpy as np
import cext07

class Particles:
    def __init__(self):
        self._p= cext07._particles_alloc()

    def __len__(self):
        return cext07._len(self._p)

    def __repr__(self):
        return cext07._as_array(self._p).__repr__()
    
    def __getitem__(self, index):
        return cext07._as_array(self._p)[index]

    def asarray(self):
        return cext07._as_array(self._p)


p = Particles()

print(p)
print(p[2:5, 1])
