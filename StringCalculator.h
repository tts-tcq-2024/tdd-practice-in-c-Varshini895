#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// Function to check if a string is empty
bool isEmptyString(const std::string& value) {
    return value.empty();
}

// Function to convert string to integer and return the value if less than 1000
int lessThanThousand(const std::string& num) {
    int input = std::stoi(num); // Convert string to integer
    if (input < 1000) {
        return input;
    }
    return 0;
}

// Function to split a string by a given delimiter
std::vector<std::string> split(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> tokens;
    std::string s = str;
    size_t pos = 0;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        tokens.push_back(s.substr(0, pos));
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);
    return tokens;
}

// Function to calculate the sum of numbers in the input string with the given delimiter
int calculateSum(const std::string& input, const std::string& delimiter) {
    int sum = 0;
    std::vector<std::string> tokens = split(input, delimiter); // Split input string
    for (const auto& token : tokens) {
        sum += lessThanThousand(token); // Add valid numbers less than 1000 to sum
    }
    return sum;
}

// Function to extract and set custom delimiter from the input string
std::string getCustomDelimiter(const std::string& input) {
    size_t end = input.find('\n');
    return input.substr(2, end - 2); // Extract the delimiter after "//" and before newline
}

// Function to check for a custom delimiter in the input and set it
std::string checkCustomDelimiter(const std::string& input, std::string& delimiter) {
    if (input.substr(0, 2) == "//") {
        delimiter = getCustomDelimiter(input); // Set custom delimiter
        return input.substr(input.find('\n') + 1); // Skip the delimiter line in input
    }
    delimiter = ",\n"; // Default delimiter is a comma and newline
    return input;
}

// Main function to add numbers in the input string
int add(const std::string& input) {
    std::string delimiter;
    if (isEmptyString(input)) {
        return 0; // Return 0 if input string is empty
    }
    std::string numbers = checkCustomDelimiter(input, delimiter); // Check for custom delimiter
    return calculateSum(numbers, delimiter); // Calculate and return sum
}

int main() {
    std::string input = "//;\n1;2;1000";  // Example input with custom delimiter
    int result = add(input);
    std::cout << "The sum is: " << result << std::endl;  // Output: The sum is: 3
    return 0;
}
