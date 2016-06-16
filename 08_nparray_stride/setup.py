import numpy as np
from distutils.core import setup, Extension

setup(name='cext08',
      version='0.0.1',
      description='c_ext08 return np.array with stride',
      author='Jun Koda',
      url='https://github.com/junkoda/python_c_ext',
      ext_modules=[
          Extension('cext08', ['cext08.c'],
                    include_dirs = [np.get_include()]),
      ],
)


