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
  // Suppose you have a data in C code and want to pass to Python as an array
  const int np=10;
  Particle* const p= calloc(sizeof(Particle), np);
  // This memory is assumed to be freed by the C code
  // (Memory leak in this example)

  int nd=2;
  int ncol= sizeof(Particle)/sizeof(float);
  npy_intp dims[]= {np, ncol};

  return PyArray_SimpleNewFromData(nd, dims, NPY_FLOAT, p);
}

static PyObject* py_read_array(PyObject *self, PyObject *args)
{
  // Read 2d array
  PyObject *bufobj;
  if(!PyArg_ParseTuple(args, "O", &bufobj))
    return NULL;

  Py_buffer view;
  if(PyObject_GetBuffer(bufobj, &view,
			PyBUF_ANY_CONTIGUOUS | PyBUF_FORMAT) == -1)
    return NULL;
  
  
  if(view.ndim != 2) {
    PyErr_SetString(PyExc_TypeError, "Expected a 2-dimensional array");
    PyBuffer_Release(&view);
    return NULL;
  }

  if(strcmp(view.format,"d") != 0) {
    PyErr_SetString(PyExc_TypeError, "Expected an array of doubles");
    PyBuffer_Release(&view);
    return NULL;
  }

  const int nrow= view.shape[0];
  const int ncol= view.shape[1];

  if(ncol < 2) {
    PyErr_SetString(PyExc_TypeError, "Expected at least two columns.");
    return NULL;
  }

  double* p= (double*) view.buf;
  const size_t next_row= view.strides[0]/sizeof(double);
  const size_t next_col= view.strides[1]/sizeof(double);
  
  for(int i=0; i<nrow; ++i) {
    double col1= *p;
    double col2= *(p + next_col);
      
    printf("%le %le\n", col1, col2);
    p += next_row;
  }

  Py_RETURN_NONE;
}

static PyMethodDef methods[] = {
  {"as_nparray", py_as_nparray, METH_VARARGS, "return a new np.array"},
  {"read_array", py_read_array, METH_VARARGS, "read an array"}, 
  {NULL, NULL, 0, NULL}
};

static struct PyModuleDef module = {
  PyModuleDef_HEAD_INIT,
  "cext04",        // name of this module
  "Use np.array",  // Doc String
  -1,
  methods
};

PyMODINIT_FUNC
PyInit_cext04(void) {
  import_array();
  return PyModule_Create(&module);
}

