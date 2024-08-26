#ifndef STRING_CALCULATOR_H
#define STRING_CALCULATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to parse a number from a token
static int parseNumber(const char* token) {
    return atoi(token);
}

// Function to check if a number should be ignored
static int shouldIgnore(int num) {
    return num > 1000;
}

// Function to extract the delimiter from the input
static char* getDelimiter(char** input) {
    if (strncmp(*input, "//", 2) == 0) {
        char* end = strchr(*input + 2, '\n');
        if (end) {
            *end = '\0';
            return strndup(*input + 2, end - (*input + 2));
        }
    }
    return strdup(","); // Default delimiter
}

// Function to handle a single token and update negatives
static int handleToken(const char* token, char* negatives) {
    int num = parseNumber(token);
    if (num < 0) {
        strcat(negatives, token);
        strcat(negatives, ",");
    }
    return num;
}

// Function to sum numbers and accumulate negatives
static int sumNumbers(char* str, const char* delimiter, char* negatives) {
    int sum = 0;
    char* token = strtok(str, delimiter);

    while (token) {
        int num = handleToken(token, negatives);
        if (!shouldIgnore(num)) {
            sum += num;
        }
        token = strtok(NULL, delimiter);
    }
    return sum;
}

// Function to process input lines and calculate the total sum
static int processInput(char* str, const char* delimiter, char* negatives) {
    int sum = 0;
    char* line = strtok(str, "\n");

    while (line) {
        sum += sumNumbers(line, delimiter, negatives);
        line = strtok(NULL, "\n");
    }

    return sum;
}

// Function to validate input
static int isInputValid(const char* input) {
    return input && strlen(input) > 0;
}

// Function to replace newlines with the delimiter
static void replaceNewlinesWithDelimiter(char* str, const char* delimiter) {
    for (char* p = str; *p; ++p) {
        if (*p == '\n') {
            *p = *delimiter;
        }
    }
}

// Function to check for negatives and handle errors
static void checkForNegatives(char* negatives) {
    if (strlen(negatives) > 0) {
        negatives[strlen(negatives) - 1] = '\0'; // Remove trailing comma
        fprintf(stderr, "negatives not allowed: %s\n", negatives);
        exit(EXIT_FAILURE);
    }
}

// Main add function to calculate the sum
static int add(const char* input) {
    if (!isInputValid(input)) {
        return 0;
    }

    char* str = strdup(input);
    if (!str) return 0; // Handle allocation failure

    char* input_copy = strdup(input);
    if (!input_copy) {
        free(str);
        return 0; // Handle allocation failure
    }

    char* delimiter = getDelimiter(&input_copy);
    if (!delimiter) {
        free(str);
        free(input_copy);
        return 0; // Handle allocation failure
    }

    char negatives[100] = "";

    replaceNewlinesWithDelimiter(str, delimiter);
    int sum = processInput(str, delimiter, negatives);
    checkForNegatives(negatives);

    free(delimiter);
    free(str);
    free(input_copy);

    return sum;
}

#endif // STRING_CALCULATOR_H
