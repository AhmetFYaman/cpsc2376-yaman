#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <chrono>
#include <thread>
#include <algorithm>
#include <cctype>
//self explanatory
inline std::string toLower(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), 
                   [](unsigned char c){ return std::tolower(c); });
    return str;
}

// Clears the input buffer
inline void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Prints a string character by character with a delay
inline void printCharByChar(const std::string& str, int delay_ms = 12) {
    for (char ch : str) {
        std::cout << ch << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }
}

// Trims leading and trailing whitespace
inline void trim(std::string& str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) { return !std::isspace(ch); }));
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), str.end());
}

// Template function for validating numerical input

template <typename T>
T getValidNumber(T minValue = T(0), T maxValue = std::numeric_limits<T>::max()) {
    std::string input;
    T value;

    while (true) {
        std::getline(std::cin, input);
        trim(input);

        if (input.empty()) {
            std::cout << "Input cannot be empty. Try again: ";
            continue;
        }

        std::stringstream ss(input);
        if (ss >> value && ss.eof() && value >= minValue && value <= maxValue) {
            return value;
        }
        std::cout << "Invalid input. Please enter a valid number between " << minValue << " and " << maxValue << ": ";
    }
}

template <typename... Args>
char getValidChar(Args... validChars) {
    std::string input;

    while (true) {
        std::getline(std::cin, input);
        trim(input);
        if (input.length() == 1 && ((input[0] == validChars) || ...)) {
            return input[0];
        }
        std::cout << "Invalid input. Please enter a valid character: ";
    }
}

// Specialized function for getting a valid binary value
inline int getValidBinary() {
    return getValidChar('0', '1') - '0';
}


template <typename... Args>
std::string getValidSingleWord(Args... validOptions) {
    std::string input;
    
    while (true) {
        std::getline(std::cin, input);
        trim(input);
        
        // Check if input is empty
        if (input.empty()) {
            printCharByChar("Input cannot be empty. Try again: ");
            continue;
        }
        
        // Check if input contains spaces
        if (input.find(' ') != std::string::npos) {
            printCharByChar("Input must be a single word with no spaces. Try again: ");
            continue;
        }
        
        // Convert input to lowercase for case-insensitive comparison
        std::string lowerInput = toLower(input);
        
        // Check if input matches any of the valid options (case-insensitive)
        if (((toLower(validOptions) == lowerInput) || ...)) {
            return lowerInput; // Return the lowercase version for consistency
        }
        
        printCharByChar("Invalid input. Please enter one of the valid options: ");
    }
}

