//
// Iterate over data in C/C++ from Python
//

#include <vector>
#include <stdexcept>
#include "Python.h"

using namespace std;

static void py_vector_free(PyObject *obj);

static PyObject* py_vector_alloc(PyObject *self, PyObject *args)
{
  // Suppose you have a data in vector in C++
  // We want to wrap this object in a Python class
  vector<double>* const v= new vector<double>();

  v->push_back(1.0);
  v->push_back(2.0);
  v->push_back(3.0);
  
  return PyCapsule_New(v, "_Vector", py_vector_free);
}

void py_vector_free(PyObject *obj)
{
  vector<double>* const v=
    (vector<double>*) PyCapsule_GetPointer(obj, "_Vector");
    
  delete v;
}

PyObject* py_vector_len(PyObject *self, PyObject *args)
{
  PyObject* py_vector;
  if(!PyArg_ParseTuple(args, "O", &py_vector))
    return NULL;

  vector<double>* const v=
    (vector<double>*) PyCapsule_GetPointer(py_vector, "_Vector");
  if(!v) return NULL;

  return Py_BuildValue("k", (unsigned long) v->size());
}


PyObject* py_vector_getitem(PyObject *self, PyObject *args)
{
  // vector_getitem(_Vector, i)
  PyObject* py_vector;
  int i;
  
  if(!PyArg_ParseTuple(args, "Oi", &py_vector, &i))
    return NULL;

  vector<double>* const v=
    (vector<double>*) PyCapsule_GetPointer(py_vector, "_Vector");
  if(!v) return NULL;

  double x;
  try {
    x= v->at(i);
  }
  catch(const std::out_of_range) {
    PyErr_SetNone(PyExc_IndexError);
    return NULL;
  }

  return Py_BuildValue("d", x);
}


static PyMethodDef methods[] = {
  {"vector_alloc", py_vector_alloc, METH_VARARGS, "allocate a vector"},
  {"vector_len", py_vector_len, METH_VARARGS, "vector.len()"},
  {"vector_getitem", py_vector_getitem, METH_VARARGS, "vector[i]"},
  {NULL, NULL, 0, NULL}
};

static struct PyModuleDef module = {
  PyModuleDef_HEAD_INIT,
  "cext05",             // name of this module
  "Use C/C++ vector",  // Doc String
  -1,
  methods
};

PyMODINIT_FUNC
PyInit_cext05(void) {  
  return PyModule_Create(&module);
}

