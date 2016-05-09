from distutils.core import setup, Extension

setup(name='cext03',
      version='0.0.1',
      description='c_ext03 filename',
      author='Jun Koda',
      url='https://github.com/junkoda/python_c_ext',
      ext_modules=[
          Extension('cext03', ['cext03.c'])
      ]
)


