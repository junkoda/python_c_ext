#include <stdio.h>

#include "Python.h"

static PyObject* hello(PyObject *self, PyObject *args)
{
  printf("Hello World!\n");
  Py_RETURN_NONE;
}

static PyMethodDef methods[] = {
  {"hello", hello, METH_VARARGS, "hello world"},
  {NULL, NULL, 0, NULL}
};

static struct PyModuleDef module = {
  PyModuleDef_HEAD_INIT,
  "cext01",              // name of this module
  "Print Hello World",   // Doc String
  -1,
  methods
};

PyMODINIT_FUNC
PyInit_cext01(void) {  
  return PyModule_Create(&module);
}

