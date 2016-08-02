python_c_ext
============

Simple examples for extending Python with C/C++

## Build

Compile the extension module:

```bash
$ cd 01_hello_world
$ python3 setup.py build_ext --inplace
```

This can be done by `make`, too:

```bash
$ make
```

Run a python script using the extension:

```bash
$ python3 ext01.py
```

## 01_hello_world

A minimum extension module.

## 02_pointer

Use C/C++ pointer from Python.

## 03_filename

Pass a filename string from Python to C/C++.

## 04_nparray

Return C/C++ data as an np.array.

## 08_nparray_stride

Return a part of C/C++ data as an np.array.

## 09_sigint

Stop Python during long computation with Ctrl-C.