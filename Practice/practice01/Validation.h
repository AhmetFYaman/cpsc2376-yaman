#pragma once

#include <iostream>
#include <string>   // For std::string
#include <sstream>  // For std::stringstream
#include <limits>   // For clearing input buffer
#include <chrono>   // For delays in printCharByChar
#include <thread>   // For std::this_thread
#include <algorithm>  // for string 
#include <cctype>   // validation
#include <cmath>

// Clears the input buffer
void clearInputBuffer() {
    std::cin.clear(); // Clear error flags
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard remaining input
}

// Prints a string character by character with a delay
void printCharByChar(const std::string& str, int delay_ms = 12) {
    for (char ch : str) {
        std::cout << ch << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }
}

std::string getValidString() {
    std::string input;

    while (true) {
        std::getline(std::cin, input);

        // Trim leading and trailing spaces
        auto trim = [](std::string& str) {
            str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
                return !std::isspace(ch);
                }));
            str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
                return !std::isspace(ch);
                }).base(), str.end());
            };

        trim(input);

        // Validate that the string is non-empty after trimming
        if (!input.empty()) {
            return input;
        }

        std::cout << "Invalid input. Please enter a non-empty string: ";
    }
}
// Validates user input for a single character ('y' or 'n')

char getValidYNChar() {
    std::string input;

    while (true) {
        std::getline(std::cin, input);

        // Trim leading and trailing spaces
        input.erase(input.begin(), std::find_if(input.begin(), input.end(), [](unsigned char ch) {
            return !std::isspace(ch);
            }));
        input.erase(std::find_if(input.rbegin(), input.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
            }).base(), input.end());

        // Validate the input
        if (input.length() == 1 && (input[0] == 'y' || input[0] == 'n')) {
            return input[0];
        }

        std::cout << "Invalid input. Please enter 'y' for yes or 'n' for no: ";
    }
}
// Valid Char
char getValidChar() {
    std::string input;

    while (true) {
        std::getline(std::cin, input);

        // Trim leading and trailing spaces
        input.erase(input.begin(), std::find_if(input.begin(), input.end(), [](unsigned char ch) {
            return !std::isspace(ch);
            }));
        input.erase(std::find_if(input.rbegin(), input.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
            }).base(), input.end());

        // Check if the input is exactly one character
        if (input.length() == 1) {
            return input[0];
        }

        std::cout << "Invalid input. Please enter exactly one character: ";
    }
}

// Validates user input for a positive integer
int getValidInteger() {
    std::string input;
    int value;

    while (true) {
        std::getline(std::cin, input);

        // Handle empty input
        if (input.empty()) {
            std::cout << "Input cannot be empty. Please enter a positive integer greater than 0: ";
            continue;
        }

        std::stringstream ss(input);

        // Attempt to extract an integer
        if (ss >> value) {
            // Check for extra characters in the input
            if (ss.eof()) {
                // Ensure the integer is positive and greater than 0
                if (value > 0) {
                    return value;
                }
                else {
                    std::cout << "Input must be a positive integer greater than 0. Try again: ";
                }
            }
            else {
                std::cout << "Invalid input. Only whole numbers are allowed. Try again: ";
            }
        }
        else {
            // Handle failed conversion
            std::cout << "Invalid input. Please enter a valid positive integer: ";
        }

        // Clear any fail flags from the stringstream
        ss.clear();
    }
}

// Validates user input for a positive floating-point number

float getValidFloat() {
    std::string input;
    float value;

    while (true) {
        std::getline(std::cin, input);

        // Handle empty input
        if (input.empty()) {
            std::cout << "Input cannot be empty. Please enter a positive floating-point number greater than 0: ";
            continue;
        }

        std::stringstream ss(input);

        // Attempt to extract a float
        if (ss >> value) {
            // Check for trailing characters in the input
            if (ss.eof()) {
                // Ensure the value is greater than 0
                if (value > 0.0f) {
                    return value;
                }
                else {
                    std::cout << "Input must be a positive number greater than 0. Try again: ";
                }
            }
            else {
                std::cout << "Invalid input. Extra characters detected. Try again: ";
            }
        }
        else {
            // Handle failed conversion
            std::cout << "Invalid input. Please enter a valid positive floating-point number: ";
        }

        // Clear the state of the stringstream
        ss.clear();
    }
}

// Validates user input for a positive double-precision number
double getValidDouble() {
    std::string input;
    double value;

    while (true) {
        std::getline(std::cin, input);

        // Handle empty input
        if (input.empty()) {
            std::cout << "Input cannot be empty. Please enter a positive double-precision number greater than 0: ";
            continue;
        }

        std::stringstream ss(input);

        // Attempt to extract a double
        if (ss >> value) {
            // Check for trailing characters in the input
            if (ss.eof()) {
                // Ensure the value is greater than 0
                if (value > 0.0) {
                    return value;
                }
                else {
                    std::cout << "Input must be a positive number greater than 0. Try again: ";
                }
            }
            else {
                std::cout << "Invalid input. Extra characters detected. Try again: ";
            }
        }
        else {
            // Handle failed conversion
            std::cout << "Invalid input. Please enter a valid positive double-precision number: ";
        }

        // Clear the state of the stringstream
        ss.clear();
    }
}

// Validates user input for a binary value ('1' or '0')

int getValidBinary() {
    std::string input;

    while (true) {
        std::getline(std::cin, input);

        // Trim leading and trailing spaces
        input.erase(input.begin(), std::find_if(input.begin(), input.end(), [](unsigned char ch) {
            return !std::isspace(ch);
            }));
        input.erase(std::find_if(input.rbegin(), input.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
            }).base(), input.end());

        // Validate the input
        if (input == "1" || input == "0") {
            return std::stoi(input);
        }

        std::cout << "Invalid input. Please enter '1' or '0': ";
    }
}

float getValidBiggerFloat(float minValue) {
    std::string input;
    float value;

    while (true) {
        std::getline(std::cin, input);

        // Handle empty input
        if (input.empty()) {
            std::cout << "Input cannot be empty. Please enter a number greater than "
                << minValue << ": ";
            continue;
        }

        std::stringstream ss(input);

        // Attempt to extract a float
        if (ss >> value) {
            // Check for extra characters in the input
            if (ss.eof()) {
                // Check if the value is greater than the minimum allowed
                if (value > minValue) {
                    return value;
                }
                else {
                    std::cout << "Input must be greater than " << minValue << ". Try again: ";
                }
            }
            else {
                std::cout << "Invalid input. Only numbers are allowed. Try again: ";
            }
        }
        else {
            // Handle failed conversion
            std::cout << "Invalid input. Please enter a valid number greater than "
                << minValue << ": ";
        }

        // Clear any fail flags from the stringstream
        ss.clear();
    }
}
