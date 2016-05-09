from distutils.core import setup, Extension

setup(name='cext02',
      version='0.0.1',
      description='c_ext02 iterate',
      author='Jun Koda',
      url='https://github.com/junkoda/python_c_ext',
      ext_modules=[
          Extension('cext05', ['cext05.cpp'])
      ]
)


