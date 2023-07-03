#include "dtypes.h"
#include "utils.cpp"

std::array<uint8_t, 14> DTYPE_TO_BYTES = {
    1, // BL08
    1, // CH08
    1, // UI08
    1, // SI08
    2, // UI16
    2, // SI16
    4, // UI32
    4, // SI32
    4, // UF32
    4, // SF32
    8, // UI64
    8, // SI64
    8, // UD64
    8, // SD64
};
std::array<std::string, 14> DTYPE_TO_NAME = {
    "BL08",
    "CH08",
    "UI08",
    "SI08",
    "UI16",
    "SI16",
    "UI32",
    "SI32",
    "UF32",
    "SF32",
    "UI64",
    "SI64",
    "UD64",
    "SD64",
};

DType::DType(const COMMON_DTYPES dtype) {
    _dtype = dtype;
    _size = DTYPE_TO_BYTES[static_cast<int>(dtype)];
}

std::string DType::to_string() {
    return string_format("DType [%s] [Size=%u]", DTYPE_TO_NAME[static_cast<int>(_dtype)].c_str(), static_cast<unsigned int>(_size));
}
