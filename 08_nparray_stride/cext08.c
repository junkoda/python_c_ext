//
// Handles numpy array
//

#include <stdio.h>
#include "Python.h"

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include "numpy/arrayobject.h"

typedef struct {
  float x[3], v[3];
} Particle;

static PyObject* py_as_nparray(PyObject *self, PyObject *args)
{
  // Suppose you have data in C code and want to pass to Python as an array
  const int np=10;
  Particle* const p= calloc(sizeof(Particle), np);

  for(int i=0; i<np; ++i) {
    p[i].x[0]= (float) i + 1;
  }
  // This memory is assumed to be freed by the C code
  // (Memory leak in this example)

  const int nd=2;
  const int ncol= 3;
  npy_intp dims[]= {np, ncol};
  npy_intp strides[]= {sizeof(Particle), sizeof(float)};

  return PyArray_New(&PyArray_Type, nd, dims, NPY_FLOAT, strides,
		     p->x, 0, 0, 0);
}

static PyMethodDef methods[] = {
  {"as_nparray", py_as_nparray, METH_VARARGS, "return a new np.array"},
  {NULL, NULL, 0, NULL}
};

static struct PyModuleDef module = {
  PyModuleDef_HEAD_INIT,
  "cext08",        // name of this module
  "Use np.array with stride",  // Doc String
  -1,
  methods
};

PyMODINIT_FUNC
PyInit_cext08(void) {
  import_array();
  return PyModule_Create(&module);
}
