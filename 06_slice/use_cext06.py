import cext06

class Vector:
    def __len__(self):
        return 10;

    def __getitem__(self, i):
        return cext06.getitem(i)
        

v = Vector()

v[1:5]

