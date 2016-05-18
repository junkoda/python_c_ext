import numpy as np
from distutils.core import setup, Extension

setup(name='cext07',
      version='0.0.1',
      description='c_ext08 container',
      author='Jun Koda',
      url='https://github.com/junkoda/python_c_ext',
      ext_modules=[
          Extension('cext07', ['cext07.cpp'],
                    include_dirs = [np.get_include()]),
      ]
)


