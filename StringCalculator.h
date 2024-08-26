#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LENGTH 1024

// Helper function to check if a character is a digit or a negative sign
int is_valid_char(char c) {
    return isdigit(c) || c == '-';
}

// Helper function to iterate over a string and apply a function to each character
int iterate_string(const char *str, int (*func)(char)) {
    while (*str != '\0') {
        if (!func(*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}

// Function to check if a string represents a number
int is_number(const char *str) {
    return iterate_string(str, is_valid_char);
}

// Function to get custom delimiters from the input string
void get_custom_delimiters(const char *input, char delimiters[MAX_INPUT_LENGTH]) {
    const char *delimiter_start = input + 2; // Skip the initial "//"
    const char *delimiter_end = strstr(input, "\n");

    if (delimiter_end != NULL) {
        strncpy(delimiters, delimiter_start, delimiter_end - delimiter_start);
        delimiters[delimiter_end - delimiter_start] = '\0';
    }
}

// Helper function to handle negatives and add valid numbers to the sum
int handle_token(const char *token, int *sum, char *negatives) {
    int num = atoi(token);
    if (num < 0) {
        strcat(negatives, token);
        strcat(negatives, " ");
    }
    if (num <= 1000) {
        *sum += num;
    }
    return 0;
}

// Function to sum valid numbers from tokens
int sum_tokens(const char *numbers, const char *delimiters) {
    int sum = 0;
    char input[MAX_INPUT_LENGTH];
    strncpy(input, numbers, MAX_INPUT_LENGTH);
    
    char negatives[MAX_INPUT_LENGTH] = "";
    char *token = strtok(input, delimiters);
    while (token != NULL) {
        if (is_number(token)) {
            handle_token(token, &sum, negatives);
        }
        token = strtok(NULL, delimiters);
    }

    if (strlen(negatives) > 0) {
        fprintf(stderr, "negatives not allowed: %s\n", negatives);
    }
    
    return sum;
}

// Function to add numbers in the string
int add(const char *input) {
    if (strlen(input) == 0) {
        return 0;
    }
    
    char delimiters[MAX_INPUT_LENGTH] = ",\n";
    const char *numbers = input;

    if (strncmp(input, "//", 2) == 0) {
        get_custom_delimiters(input, delimiters);
        numbers = strstr(input, "\n") + 1;

        // Replace custom delimiters with '\n' for easier tokenization
        for (char *d = delimiters; *d != '\0'; d++) {
            if (*d == ',') {
                *d = '\n';
            }
        }
    }
    
    return sum_tokens(numbers, delimiters);
}

int main() {
    char input[MAX_INPUT_LENGTH];
    printf("Enter the string of numbers: ");
    fgets(input, MAX_INPUT_LENGTH, stdin);
    
    int result = add(input);
    printf("The sum is: %d\n", result);

    return 0;
}
