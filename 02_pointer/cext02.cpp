//
// Return C/C++ pointer as a Python Object
//

#include <cstdio>
#include "Python.h"

static void py_hello_free(PyObject *obj);

class Hello {
 public:
  void hello();
};

void Hello::hello()
{
  printf("Hello World!\n");
}

static PyObject* py_hello_alloc(PyObject *self, PyObject *args)
{
  // Allocate a new C++ pointer h as a Python object "_Hello"
  Hello* const h= new Hello();
  
  return PyCapsule_New(h, "_Hello", py_hello_free);
}

void py_hello_free(PyObject *obj)
{
  // Destructor function for _Hello pointer, called automatically from Python
  Hello* const h= (Hello*) PyCapsule_GetPointer(obj, "_Hello");
    
  delete h;
}

PyObject* py_hello(PyObject *self, PyObject *args)
{
  // Use _Hello pointer from Python
  // _hello(_Hello h)

  PyObject* py_obj;
  
  if(!PyArg_ParseTuple(args, "O", &py_obj))
    return NULL;

  Hello* h= (Hello*) PyCapsule_GetPointer(py_obj, "_Hello");
  if(!h) return NULL;

  h->hello();

  Py_RETURN_NONE;
}

static PyMethodDef methods[] = {
  {"hello_alloc", py_hello_alloc, METH_VARARGS, "allocate a Hello object"},
  {"hello",       py_hello,       METH_VARARGS, "allocate a Hello object"},
  {NULL, NULL, 0, NULL}
};

static struct PyModuleDef module = {
  PyModuleDef_HEAD_INIT,
  "cext02",              // name of this module
  "Use C/C++ pointer",  // Doc String
  -1,
  methods
};

PyMODINIT_FUNC
PyInit_cext02(void) {  
  return PyModule_Create(&module);
}

