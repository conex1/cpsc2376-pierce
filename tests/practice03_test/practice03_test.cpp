#include <gtest/gtest.h>
#include "practice03.cpp"

TEST(MathUtilsTest, SumRangeInclusive) {
    EXPECT_EQ(MathUtils::sumRange(1, 5), 15);
    EXPECT_EQ(MathUtils::sumRange(3, 3), 3);
    EXPECT_EQ(MathUtils::sumRange(-2, 2), 0);
}

TEST(MathUtilsTest, ContainsNegative) {
    std::vector<int> v1 = {3, -1, 5, 7};
    EXPECT_TRUE(MathUtils::containsNegative(v1));
    std::vector<int> v2 = {1, 2, 3};
    EXPECT_FALSE(MathUtils::containsNegative(v2));
    std::vector<int> v3 = {-2, -3};
    EXPECT_TRUE(MathUtils::containsNegative(v3));
    std::vector<int> v4 = {};
    EXPECT_FALSE(MathUtils::containsNegative(v4));
}

TEST(MathUtilsTest, FindMax) {
    std::vector<int> v1 = {3, -1, 5, 7};
    EXPECT_EQ(MathUtils::findMax(v1), 7);
    std::vector<int> v2 = {};
    EXPECT_THROW(MathUtils::findMax(v2), std::runtime_error);
    std::vector<int> v3 = {5};
    EXPECT_EQ(MathUtils::findMax(v3), 5);
    std::vector<int> v4 = {-3, -1, -5};
    EXPECT_EQ(MathUtils::findMax(v4), -1);
}