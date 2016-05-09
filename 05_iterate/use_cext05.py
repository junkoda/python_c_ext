import cext05

class Vector:
    def __init__(self):
        self._v = cext05.vector_alloc()

    def __len__(self):
        return cext05.vector_len(self._v)

    def __getitem__(self, i):
        return cext05.vector_getitem(self._v, i)

v = Vector()

print('len(v) = %d' % len(v))

print('for loop')
for x in v:
    print(x)

print('v[1]= %.1f' % v[1])

