//
// Handles slicing array[i:j:k]
//

#include <iostream>
#include <vector>
#include <stdexcept>
#include "Python.h"

using namespace std;

static const int dat[]= {0,1,2,3,4,5,6,7,8,9};
static const int n= 10;

PyObject* py_getitem(PyObject *self, PyObject *args)
{
  PyObject* py_index;
  if(!PyArg_ParseTuple(args, "O", &py_index))
    return NULL;

  if(PyNumber_Check(py_index)) {
    cout << "Number given\n";
    long index= PyLong_AsLong(py_index);
    if(PyErr_Occurred())
      return NULL;

    if(index < 0)
      index = n - index;

    if(index < 0 || index >= n) {
      PyErr_SetNone(PyExc_IndexError);
      return NULL;
    }
    
    return Py_BuildValue("i", dat[index]);
  }
  else if(PySequence_Check(py_index)) {
    cout << "Sequience given\n";

    Py_ssize_t len= PySequence_Length(py_index);
    PyObject* const list= PyList_New(len);

    for(Py_ssize_t i=0; i<len; ++i) {
      PyObject* e= PySequence_GetItem(py_index, i);
      long index= PyLong_AsLong(e);
      if(PyErr_Occurred())
	return NULL;

      if(index < 0 || index >= n) {
	PyErr_SetNone(PyExc_IndexError);
	return NULL;
      }
      
      PyList_SetItem(list, i, Py_BuildValue("i", dat[index]));
    }
    return list;
  }
  else if(PySlice_Check(py_index)) {
    cout << "Slice object given\n";
    Py_ssize_t start, stop, step, length;
    int ret= PySlice_GetIndicesEx(py_index, n, &start, &stop, &step, &length);
    if(ret)
      return NULL;

    int len= (stop - start)/step;
    printf("len= %d\n", len);
    
    PyObject* const list= PyList_New(len);

    int index=0;
    for(int i=start; i<stop; i+=step) {
      PyList_SetItem(list, index++, Py_BuildValue("i", dat[i]));
    }
    return list;
  }
  

  Py_RETURN_NONE;
}


static PyMethodDef methods[] = {
  {"getitem", py_getitem, METH_VARARGS, "array[] operator"},
  {NULL, NULL, 0, NULL}
};

static struct PyModuleDef module = {
  PyModuleDef_HEAD_INIT,
  "cext06",             // name of this module
  "Handles array slicing",  // Doc String
  -1,
  methods
};

PyMODINIT_FUNC
PyInit_cext06(void) {  
  return PyModule_Create(&module);
}

