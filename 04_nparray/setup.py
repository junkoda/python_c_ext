import numpy as np
from distutils.core import setup, Extension

setup(name='cext04',
      version='0.0.1',
      description='c_ext04 use np.array',
      author='Jun Koda',
      url='https://github.com/junkoda/python_c_ext',
      ext_modules=[
          Extension('cext04', ['cext04.c'],
                    include_dirs = [np.get_include()]),
      ],
)


