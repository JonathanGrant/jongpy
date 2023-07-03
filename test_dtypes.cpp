#include <gtest/gtest.h>
#include "dtypes.h"

// Test if the size and dtype member variables are initialized correctly
TEST(DTypeTest, InitializationTest) {
    DType d1(COMMON_DTYPES::UI08);
    EXPECT_EQ(d1.size(), 1);
    EXPECT_EQ(d1.dtype(), COMMON_DTYPES::UI08);
    
    DType d2(COMMON_DTYPES::SI32);
    EXPECT_EQ(d2.size(), 4);
    EXPECT_EQ(d2.dtype(), COMMON_DTYPES::SI32);

    DType d3(COMMON_DTYPES::SD64);
    EXPECT_EQ(d3.size(), 8);
    EXPECT_EQ(d3.dtype(), COMMON_DTYPES::SD64);
}

// Test if the to_string method returns the correct string representation
TEST(DTypeTest, ToStringTest) {
    DType d1(COMMON_DTYPES::UI08);
    std::string expected_str1 = "DType [UI08] [Size=1]";
    EXPECT_EQ(d1.to_string(), expected_str1);
    
    DType d2(COMMON_DTYPES::SI32);
    std::string expected_str2 = "DType [SI32] [Size=4]";
    EXPECT_EQ(d2.to_string(), expected_str2);

    DType d3(COMMON_DTYPES::SD64);
    std::string expected_str3 = "DType [SD64] [Size=8]";
    EXPECT_EQ(d3.to_string(), expected_str3);
}
