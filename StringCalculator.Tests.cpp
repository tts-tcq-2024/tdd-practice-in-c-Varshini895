#include <gtest/gtest.h>
#include "StringCalculator.h"

// Test case for an empty input string
TEST(StringCalculatorAddTests, ExpectZeroForEmptyInput) {
    int expectedresult = 0;
    const std::string input = "";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

// Test case for a single zero
TEST(StringCalculatorAddTests, ExpectZeroForSingleZero) {
    int expectedresult = 0;
    const std::string input = "0";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

// Test case for two numbers
TEST(StringCalculatorAddTests, ExpectSumForTwoNumbers) {
    int expectedresult = 3;
    const std::string input = "1,2";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

// Test case for handling newlines as delimiters
TEST(StringCalculatorAddTests, ExpectSumWithNewlineDelimiter) {
    int expectedresult = 6;
    const std::string input = "1\n2,3";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

// Test case for ignoring numbers greater than 1000
TEST(StringCalculatorAddTests, IgnoreNumbersGreaterThan1000) {
    int expectedresult = 1;
    const std::string input = "1,1001";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

// Test case for custom delimiter
TEST(StringCalculatorAddTests, ExpectSumWithCustomDelimiter) {
    int expectedresult = 3;
    const std::string input = "//;\n1;2";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

// Test case for handling negative numbers (if such cases should be handled, modify your implementation accordingly)
TEST(StringCalculatorAddTests, ExpectSumWithNegativeNumbers) {
    int expectedresult = -1; // Adjust based on whether negatives should be included or not
    const std::string input = "1,-2";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

// Test case for handling an empty string with delimiters
TEST(StringCalculatorAddTests, ExpectSumEmptyString) {
    int expectedresult = 0;
    const std::string input = ",\n";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

// Test case for custom delimiter with incorrect format
TEST(StringCalculatorAddTests, ExpectWithCustomDelimiter_1) {
    int expectedresult = 0;
    const std::string input = "//;some_delim";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

// Test case for input with no valid delimiters
TEST(StringCalculatorAddTests, ExpectWithCustomDelimiter_2) {
    int expectedresult = 0;
    const std::string input = "/some/other/text";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}
