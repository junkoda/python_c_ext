from distutils.core import setup, Extension

setup(name='cext01',
      version='0.0.1',
      description='c_ext01 hello world',
      author='Jun Koda',
      url='https://github.com/junkoda/python_c_ext',
      ext_modules=[
          Extension('cext01', ['cext01.c'])
      ]
)


