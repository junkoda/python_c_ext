from distutils.core import setup, Extension

setup(name='cext06',
      version='0.0.1',
      description='c_ext06 iterate',
      author='Jun Koda',
      url='https://github.com/junkoda/python_c_ext',
      ext_modules=[
          Extension('cext06', ['cext06.cpp'])
      ]
)


