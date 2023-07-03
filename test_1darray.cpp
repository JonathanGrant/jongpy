#include <gtest/gtest.h>
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
