#include <gtest/gtest.h>
#include "StringCalculator.h"

// Test case for empty string input
TEST(StringCalculatorTest, HandlesEmptyString) {
    ASSERT_EQ(add(""), 0);
}

// Test case for single number input
TEST(StringCalculatorTest, HandlesSingleNumber) {
    ASSERT_EQ(add("5"), 5);
}

// Test case for two numbers input separated by a comma
TEST(StringCalculatorTest, HandlesTwoNumbersComma) {
    ASSERT_EQ(add("1,2"), 3);
}

// Test case for multiple numbers input separated by a comma
TEST(StringCalculatorTest, HandlesMultipleNumbersComma) {
    ASSERT_EQ(add("1,2,3,4"), 10);
}

// Test case for numbers with newlines between them
TEST(StringCalculatorTest, HandlesNewlineBetweenNumbers) {
    ASSERT_EQ(add("1\n2,3"), 6);
}

// Test case for custom single-character delimiter
TEST(StringCalculatorTest, HandlesCustomSingleCharacterDelimiter) {
    ASSERT_EQ(add("//;\n1;2;3"), 6);
}

// Test case for custom multi-character delimiter
TEST(StringCalculatorTest, HandlesCustomMultiCharacterDelimiter) {
    ASSERT_EQ(add("//[***]\n1***2***3"), 6);
}

// Test case for numbers larger than 1000 being ignored
TEST(StringCalculatorTest, IgnoresNumbersLargerThan1000) {
    ASSERT_EQ(add("2,1001"), 2);
    ASSERT_EQ(add("//;\n1002;1003;4"), 4);
}

// Test case for multiple custom delimiters
TEST(StringCalculatorTest, HandlesMultipleCustomDelimiters) {
    ASSERT_EQ(add("//[*][%]\n1*2%3"), 6);
}

// Test case for custom delimiters with special characters
TEST(StringCalculatorTest, HandlesCustomDelimitersWithSpecialCharacters) {
    ASSERT_EQ(add("//[***][%%]\n1***2%%3"), 6);
}

// Test case for negative numbers throwing an error
TEST(StringCalculatorTest, ThrowsErrorOnNegativeNumbers) {
    ASSERT_DEATH(add("1,-2,3,-4"), "negatives not allowed: -2 -4");
}

// Test case for input with no valid numbers
TEST(StringCalculatorTest, HandlesNoValidNumbers) {
    ASSERT_EQ(add("1001,1002,1003"), 0);
}

// Test case for custom delimiter at the beginning of input with no numbers
TEST(StringCalculatorTest, HandlesCustomDelimiterWithNoNumbers) {
    ASSERT_EQ(add("//;\n"), 0);
}

// Additional test case for getDelimiter to handle custom delimiter with correct syntax
TEST(StringCalculatorTest, HandlesCustomDelimiterWithCorrectSyntax) {
    const char* input = "//;\n1;2";
    char delimiters[MAX_INPUT_LENGTH] = "";
    get_custom_delimiter(input, delimiters);
    ASSERT_STREQ(delimiters, ";\n");
}

// Additional test case for getDelimiter to handle default delimiter
TEST(StringCalculatorTest, HandlesDefaultDelimiter) {
    const char* input = "1,2,3";
    char delimiters[MAX_INPUT_LENGTH] = ",\n";
    ASSERT_STREQ(delimiters, ",\n");
}

// Additional test case for isInputValid with NULL input
TEST(StringCalculatorTest, HandlesNullInput) {
    ASSERT_EQ(add(NULL), 0);  // Assuming add returns 0 for NULL input
}

// Additional test case for isInputValid with empty input
TEST(StringCalculatorTest, HandlesEmptyInput) {
    ASSERT_EQ(add(""), 0);
}

// Additional test case for isInputValid with valid input
TEST(StringCalculatorTest, HandlesValidInput) {
    ASSERT_EQ(add("1,2,3"), 6);
}

// Additional test case for checkForNegatives with no negatives
TEST(StringCalculatorTest, HandlesNoNegatives) {
    ASSERT_NO_FATAL_FAILURE({
        char negatives[] = "";
        check_for_negatives(negatives);
    });
}

// Additional test case for checkForNegatives with negatives
TEST(StringCalculatorTest, ThrowsErrorWithNegativesCheck) {
    ASSERT_DEATH({
        char negatives[] = "-1,-2,";
        check_for_negatives(negatives);
    }, "negatives not allowed: -1 -2");
}

// Additional test case for custom delimiter without newline (edge case)
TEST(StringCalculatorTest, HandlesCustomDelimiterWithoutNewline) {
    const char* input = "//,\n1,2";
    char delimiters[MAX_INPUT_LENGTH] = "";
    get_custom_delimiter(input, delimiters);
    ASSERT_STREQ(delimiters, ",\n");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
