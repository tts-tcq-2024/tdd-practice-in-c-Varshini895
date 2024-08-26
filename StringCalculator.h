#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib> // for std::atoi
#include <cstring> // for std::strdup and std::strtok

// Function to check if a string is empty or NULL
bool isEmptyString(const std::string& value) {
    return value.empty() || value == "0";
}

// Function to convert string to integer and return value if less than 1000
int lessThanThousand(const std::string& num) {
    int input = std::atoi(num.c_str()); // Convert string to integer
    if (input < 1000) {
        return input;
    }
    return 0;
}

// Function to split a string by a given delimiter and calculate sum
int calculateSum(const std::string& input, const std::string& delimiter) {
    int sum = 0;
    std::string s = input;
    size_t pos = 0;
    std::string token;
    
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        sum += lessThanThousand(token); // Add valid numbers less than 1000 to sum
        s.erase(0, pos + delimiter.length());
    }
    sum += lessThanThousand(s); // Add the last token
    return sum;
}

// Function to extract custom delimiter from input string
std::string getCustomDelimiter(const std::string& input) {
    size_t end = input.find('\n');
    return input.substr(2, end - 2); // Extract delimiter after "//" and before newline
}

// Function to check and set custom delimiter
std::string checkCustomDelimiter(const std::string& input) {
    if (input.substr(0, 2) == "//") {
        return getCustomDelimiter(input); // Set custom delimiter
    }
    return ",\n"; // Default delimiter is a comma and newline
}

// Main function to add numbers in the input string
int add(const std::string& input) {
    if (isEmptyString(input)) {
        return 0; // Return 0 if input string is empty
    }
    std::string delimiter = checkCustomDelimiter(input); // Check for custom delimiter
    std::string numbers = (delimiter == ",\n") ? input : input.substr(input.find('\n') + 1); // Extract numbers part
    return calculateSum(numbers, delimiter); // Calculate and return sum
}

int main() {
    std::string input = "//;\n1;2";  // Example input with custom delimiter
    int result = add(input);
    std::cout << "The sum is: " << result << std::endl;  // Output: The sum is: 3
    return 0;
}
