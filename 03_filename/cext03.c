//
// Pass filename to C extention
//

#include <stdio.h>
#include "Python.h"

static PyObject* hello_file(PyObject *self, PyObject *args)
{
  // py_filename(filename)
  //
  // Convert Python string to char* filename
  //
  PyObject* bytes;

  if(!PyArg_ParseTuple(args, "O&", PyUnicode_FSConverter, &bytes)) {
    return NULL;
  }

  char* filename;
  Py_ssize_t len;
  PyBytes_AsStringAndSize(bytes, &filename, &len);

  FILE* const fp= fopen(filename, "w");

  if(fp == NULL) {
    PyErr_SetString(PyExc_IOError, "Error: unable to open file");
    return NULL;
  }

  fprintf(fp, "Hello World!\n");
  fclose(fp);  

  Py_DECREF(bytes);

  Py_RETURN_NONE;
}

static PyMethodDef methods[] = {
  {"hello_file", hello_file, METH_VARARGS, "pass filename to C extention"},
  {NULL, NULL, 0, NULL}
};

static struct PyModuleDef module = {
  PyModuleDef_HEAD_INIT,
  "cext03",             // name of this module
  "Use C/C++ pointer",  // Doc String
  -1,
  methods
};

PyMODINIT_FUNC
PyInit_cext03(void) {  
  return PyModule_Create(&module);
}

