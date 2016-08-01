//
// How to stop Python C-extension with Ctrl+C
//
#include <stdio.h>
#include <stdlib.h>
#include "Python.h"

void sigint_handler(int signo) {
  printf("recieved SIGINT");
  abort();
}

static PyObject* long_computation(PyObject *self, PyObject *args)
{
  const size_t n=  1L << 30;

  printf("Sum of 1/1 + 1/2 + ... + 1/%lu = ... ", n); fflush(stdout);

  double sum_inv= 0;

  Py_BEGIN_ALLOW_THREADS
  for(size_t i=1; i<=n; ++i)
    sum_inv += 1.0/i;
  Py_END_ALLOW_THREADS
   
  printf(" = %lf\n", sum_inv);
  
  Py_RETURN_NONE;
}

static PyMethodDef methods[] = {
  {"long_computation", long_computation, METH_VARARGS, "A long computation"},
  {NULL, NULL, 0, NULL}
};

static struct PyModuleDef module = {
  PyModuleDef_HEAD_INIT,
  "cext09",           // name of this module
  "Handles ctrl+c",   // Doc String
  -1,
  methods
};

PyMODINIT_FUNC
PyInit_cext09(void) {
  //signal(SIGINT, sigint_handler);
  return PyModule_Create(&module);
}
