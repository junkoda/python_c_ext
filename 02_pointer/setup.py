from distutils.core import setup, Extension

setup(name='cext02',
      version='0.0.1',
      description='c_ext02 pointer',
      author='Jun Koda',
      url='https://github.com/junkoda/python_c_ext',
      ext_modules=[
          Extension('cext02', ['cext02.cpp'])
      ]
)


