from distutils.core import setup, Extension

setup(name='cext05',
      version='0.0.1',
      description='c_ext05 iterate',
      author='Jun Koda',
      url='https://github.com/junkoda/python_c_ext',
      ext_modules=[
          Extension('cext05', ['cext05.cpp'])
      ]
)


