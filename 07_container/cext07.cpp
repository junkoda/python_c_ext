//
// Python class vector<Particle>
//

#include <iostream>
#include <vector>
#include <stdexcept>
#include "Python.h"

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include "numpy/arrayobject.h"

using namespace std;

struct Particle {
  float x[3], v[3];
};

static void py_particles_free(PyObject *obj);

PyObject* py_particles_alloc(PyObject *self, PyObject *args)
{
  // Allocate a new C++ pointer as a Python object "_Particles"
  vector<Particle>* const p= new vector<Particle>();

  p->resize(10);
  
  return PyCapsule_New(p, "_Particles", py_particles_free);
}

void py_particles_free(PyObject *obj)
{
  // Destructor function for _Particles pointer,called automatically from Python
  vector<Particle>* const p=
    (vector<Particle>*) PyCapsule_GetPointer(obj, "_Particles");
    
  delete p;
}

PyObject* py_len(PyObject *self, PyObject *args)
{
  PyObject* py_particles;
  if(!PyArg_ParseTuple(args, "O", &py_particles))
    return NULL;

  vector<Particle>* const p=
    (vector<Particle>*) PyCapsule_GetPointer(py_particles, "_Particles");
  if(!p)
    return NULL;

  return Py_BuildValue("k", (unsigned long) p->size());
}

PyObject* py_as_array(PyObject *self, PyObject *args)
{
  PyObject* py_particles;
  if(!PyArg_ParseTuple(args, "O", &py_particles))
    return NULL;

  vector<Particle>* const p=
    (vector<Particle>*) PyCapsule_GetPointer(py_particles, "_Particles");
  if(!p) return NULL;

  int nd=2;
  int ncol= sizeof(Particle)/sizeof(float);
  npy_intp dims[]= {(npy_intp) p->size(), ncol};

  return PyArray_SimpleNewFromData(nd, dims, NPY_FLOAT, &(p->front()));
}


static PyMethodDef methods[] = {
  {"_particles_alloc", py_particles_alloc, METH_VARARGS, "new Particles"},
  {"_as_array", py_as_array, METH_VARARGS, "vector<Particle> as an array"},
  {"_len", py_len, METH_VARARGS, "vector.size"},
  {NULL, NULL, 0, NULL}
};

static struct PyModuleDef module = {
  PyModuleDef_HEAD_INIT,
  "cext07",                // name of this module
  "Use vector<Particle>",  // Doc String
  -1,
  methods
};

PyMODINIT_FUNC
PyInit_cext07(void) {
  import_array();
  return PyModule_Create(&module);
}

