#include <gtest/gtest.h>
#include <random>
#include <typeinfo>

#include "1darray.h"

// Test for the initialization and length of the array
TEST(OneDArrayTest, InitializationAndLengthTest) {
    unsigned char data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    DType dtype(COMMON_DTYPES::UI08);
    OneDArray array(data, dtype, 10);
    
    EXPECT_EQ(array.length(), 10);
}

// Test for accessing elements of the array with correct types
TEST(OneDArrayTest, AccessElementsTest) {
    unsigned char data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    DType dtype(COMMON_DTYPES::UI08);
    OneDArray array(data, dtype, 10);

    EXPECT_EQ(array.getElement<unsigned char>(0), 1);
    EXPECT_EQ(array.getElement<unsigned char>(9), 10);
}

// Test for accessing elements out of bounds
TEST(OneDArrayTest, OutOfBoundsTest) {
    unsigned char data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    DType dtype(COMMON_DTYPES::UI08);
    OneDArray array(data, dtype, 10);

    EXPECT_THROW(array.getElement<unsigned char>(10), std::invalid_argument);
}

TEST(OneDArrayTest, HighStrideAccessTest) {
    unsigned char data[40] = {0};  // Create an array that can hold 10 float32 values
    float value1 = 3.14f;
    float value2 = 2.71f;

    // Write raw bytes of value1 and value2 into the data array
    for(int i = 0; i < 10; i++) *reinterpret_cast<float*>(&data[i*4]) = (i/10.0f);
    *reinterpret_cast<float*>(&data[0]) = value1;
    *reinterpret_cast<float*>(&data[8]) = value2;

    // Create an instance of OneDArray
    DType dtype(COMMON_DTYPES::SF32);
    OneDArray array(data, dtype, 10, 2);  // Using a stride of 2 (8 bytes)

    // Access the raw bytes and convert them to floats
    float retrievedValue1 = array.getElement<float>(0);
    float retrievedValue2 = array.getElement<float>(1);

    // Validate the results
    EXPECT_FLOAT_EQ(retrievedValue1, value1);
    EXPECT_FLOAT_EQ(retrievedValue2, value2);
}

TEST(OneDArrayTest, RandomizedAccessTest) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> stride_dis(1, 4);
    std::uniform_int_distribution<> index_dis(0, 2);
    std::uniform_int_distribution<> bool_dis(0, 1);
    std::uniform_int_distribution<> char_dis(0, 127);
    std::uniform_int_distribution<> uint8_dis(0, 255);
    std::uniform_int_distribution<> int8_dis(-126, 126);
    std::uniform_int_distribution<> uint16_dis(0, 65535);
    std::uniform_int_distribution<> int16_dis(-32767, 32767);
    std::uniform_int_distribution<uint32_t> uint32_dis(0, 4294967295);
    std::uniform_int_distribution<int32_t> int32_dis(-2147483647, 2147483647);
    std::uniform_int_distribution<uint64_t> uint64_dis(0, 18446744073709551615ULL);
    std::uniform_int_distribution<int64_t> int64_dis(-9223372036854775808LL, 9223372036854775807LL);
    std::uniform_real_distribution<float> sfloat_dis(-100.0f, 100.0f);
    std::uniform_real_distribution<double> sdouble_dis(-200.0f, 200.0f);

    // Buffer to hold the data (enough to hold some values with strides)
    unsigned char data[1024];

    // Loop through each dtype in the enum
    for (int i = 0; i < 12; ++i) {
        COMMON_DTYPES dtype_enum = static_cast<COMMON_DTYPES>(i);
        DType dtype(dtype_enum);

        // Get random stride and index
        size_t stride = stride_dis(gen);
        size_t index = index_dis(gen);

        // Write values based on dtype
        switch (dtype_enum) {
            case COMMON_DTYPES::BL08: {
                OneDArray array(data, dtype, 10, stride);
                uint8_t random_value = static_cast<uint8_t>(bool_dis(gen));
                array.getElement<uint8_t>(index) = random_value;
                EXPECT_EQ(array.getElement<uint8_t>(index), random_value);
                break;
            }
            case COMMON_DTYPES::CH08: {
                OneDArray array(data, dtype, 10, stride);
                char random_value = static_cast<char>(char_dis(gen));
                array.getElement<char>(index) = random_value;
                EXPECT_EQ(array.getElement<char>(index), random_value);
                break;
            }
            case COMMON_DTYPES::UI08: {
                OneDArray array(data, dtype, 10, stride);
                uint8_t random_value = static_cast<uint8_t>(uint8_dis(gen));
                array.getElement<uint8_t>(index) = random_value;
                EXPECT_EQ(array.getElement<uint8_t>(index), random_value);
                break;
            }
            case COMMON_DTYPES::SI08: {
                OneDArray array(data, dtype, 10, stride);
                int8_t random_value = static_cast<int8_t>(int8_dis(gen));
                array.getElement<int8_t>(index) = random_value;
                EXPECT_EQ(array.getElement<int8_t>(index), random_value);
                break;
            }
            case COMMON_DTYPES::UI16: {
                OneDArray array(data, dtype, 10, stride);
                uint16_t random_value = static_cast<uint16_t>(uint16_dis(gen));
                array.getElement<uint16_t>(index) = random_value;
                EXPECT_EQ(array.getElement<uint16_t>(index), random_value);
                break;
            }
            case COMMON_DTYPES::SI16: {
                OneDArray array(data, dtype, 10, stride);
                int16_t random_value = static_cast<int16_t>(int16_dis(gen));
                array.getElement<int16_t>(index) = random_value;
                EXPECT_EQ(array.getElement<int16_t>(index), random_value);
                break;
            }
            case COMMON_DTYPES::UI32: {
                OneDArray array(data, dtype, 10, stride);
                uint32_t random_value = static_cast<uint32_t>(uint32_dis(gen));
                array.getElement<uint32_t>(index) = random_value;
                EXPECT_EQ(array.getElement<uint32_t>(index), random_value);
                break;
            }
            case COMMON_DTYPES::SI32: {
                OneDArray array(data, dtype, 10, stride);
                int32_t random_value = static_cast<int32_t>(int32_dis(gen));
                array.getElement<int32_t>(index) = random_value;
                EXPECT_EQ(array.getElement<int32_t>(index), random_value);
                break;
            }
            case COMMON_DTYPES::UI64: {
                OneDArray array(data, dtype, 10, stride);
                uint64_t random_value = static_cast<uint64_t>(uint64_dis(gen));
                array.getElement<uint64_t>(index) = random_value;
                EXPECT_EQ(array.getElement<uint64_t>(index), random_value);
                break;
            }
            case COMMON_DTYPES::SI64: {
                OneDArray array(data, dtype, 10, stride);
                int64_t random_value = static_cast<int64_t>(int64_dis(gen));
                array.getElement<int64_t>(index) = random_value;
                EXPECT_EQ(array.getElement<int64_t>(index), random_value);
                break;
            }
            case COMMON_DTYPES::SF32: {
                OneDArray array(data, dtype, 10, stride);
                float random_value = sfloat_dis(gen);
                array.getElement<float>(index) = random_value;
                EXPECT_FLOAT_EQ(array.getElement<float>(index), random_value);
                break;
            }
            case COMMON_DTYPES::SD64: {
                OneDArray array(data, dtype, 10, stride);
                double random_value = sdouble_dis(gen);
                array.getElement<double>(index) = random_value;
                EXPECT_DOUBLE_EQ(array.getElement<double>(index), random_value);
                break;
            }
            // Handle other cases similarly...
            default:
                break;
        }
    }
}

TEST(OneDArrayTest, CopyConstructorTest) {
    unsigned char data[40] = {0};  
    for(int i = 0; i < 10; i++) *reinterpret_cast<float*>(&data[i*4]) = (i/10.0f);
    
    DType dtype(COMMON_DTYPES::SF32);
    OneDArray original(data, dtype, 10);  // Create an instance of OneDArray

    // Use the copy constructor
    OneDArray copy(original);

    // Validate the results
    EXPECT_EQ(copy.length(), original.length());
    EXPECT_EQ(copy.dtype(), original.dtype());
    EXPECT_EQ(copy.stride(), original.stride());

    for (size_t i = 0; i < original.length(); i++) {
        EXPECT_FLOAT_EQ(copy.getElement<float>(i), original.getElement<float>(i));
    }
}
