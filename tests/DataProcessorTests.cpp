#include <gtest/gtest.h>
#include "DataProcessorUtils.h"


class UtilsTest : public ::testing::Test {
protected:
    DataProcessorUtils utils;
};

TEST_F(UtilsTest, RemovesDuplicates) {
    std::string input = "apple banana apple";
    std::string expected = "apple banana";
    EXPECT_EQ(utils.processData(input), expected);
}

TEST_F(UtilsTest, HandlesPunctuation) {
    std::string input = "hello,world!hello";
    std::string expected = "hello world";
    EXPECT_EQ(utils.processData(input), expected);
}

TEST_F(UtilsTest, InvalidCharacters) {
    std::string input = "test123";
    std::string expected = "Invalid input: non-alphabetic characters or invalid format";
    EXPECT_EQ(utils.processData(input), expected);
}

TEST_F(UtilsTest, OnlyInvalidCharacters) {
    std::string input = "434 .34 , ;%$*# !";
    std::string expected = "Invalid input: non-alphabetic characters or invalid format";
    EXPECT_EQ(utils.processData(input), expected);
}

TEST_F(UtilsTest, MultipleSpaces) {
    std::string input = "   hello   world   ";
    std::string expected = "hello world";
    EXPECT_EQ(utils.processData(input), expected);
}

TEST_F(UtilsTest, CaseSensitivity) {
    std::string input = "Apple apple Banana";
    std::string expected = "Apple apple Banana";
    EXPECT_EQ(utils.processData(input), expected);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}