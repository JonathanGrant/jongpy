#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include "dtypes.h"
#include "1darray.h"

namespace py = pybind11;

PYBIND11_MODULE(jongpy_bindings, m) {
    py::enum_<COMMON_DTYPES>(m, "COMMON_DTYPES");
    py::class_<DType>(m, "DType")
        .def(py::init<const COMMON_DTYPES>())
        .def("size", &DType::size)
        .def("dtype", &DType::dtype)
        .def("to_string", &DType::to_string);
        // add other operations
}
/*
.def("__getitem__",
        [](const Matrix &m, std::pair<size_t, size_t> ij) {
            return m(ij.first, ij.second);
        })
.def("__setitem__",
        [](Matrix &m, std::pair<size_t, size_t> ij, float val) {
            m(ij.first, ij.second) = val;
        })
*/