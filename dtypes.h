#include <cstdint>
#include <string>
#include <array>

enum COMMON_DTYPES {
    BL08, CH08,
    UI08, SI08,
    UI16, SI16,
    UI32, SI32,
    SF32,
    UI64, SI64,
    SD64,
};

extern std::array<uint8_t, 12> DTYPE_TO_BYTES;
extern std::array<std::string, 12> DTYPE_TO_NAME;

class DType {
    public:
        DType(const COMMON_DTYPES dtype);
        uint8_t size() const { return _size; };
        COMMON_DTYPES dtype() const { return _dtype; };
        std::string to_string();

        bool operator==(const DType& other) const {
            return this->dtype() == other.dtype();
        }
    
    private:
        uint8_t _size;
        COMMON_DTYPES _dtype;

};
