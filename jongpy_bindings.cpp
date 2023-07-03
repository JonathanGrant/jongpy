#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include "matrix.h"

namespace py = pybind11;

PYBIND11_MODULE(jongpy_bindings, m) {
    py::class_<Matrix>(m, "Matrix")
        .def(py::init<size_t, size_t>())
        .def("__getitem__",
             [](const Matrix &m, std::pair<size_t, size_t> ij) {
                 return m(ij.first, ij.second);
             })
        .def("__setitem__",
             [](Matrix &m, std::pair<size_t, size_t> ij, float val) {
                 m(ij.first, ij.second) = val;
             })
        .def("add", &Matrix::add)
        .def("log", &Matrix::log);
        // add other operations
}
