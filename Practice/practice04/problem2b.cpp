#include "ValidationPro.h"
#include <iostream>
#include <string>
#include <algorithm> // for max math


template <typename T>
T findMax(T a, T b, T c) {
    return std::max({a, b, c});
}

int main() {
    int choice;
    std::cout << "Compare (1) Numbers or (2) Strings? ";
    choice = getValidNumber<int>(1); 

    if (choice == 1) {
       
        int a, b, c;
        std::cout << "Enter first value: ";
        a = getValidNumber<int>();
        std::cout << "Enter second value: ";
        b = getValidNumber<int>();
        std::cout << "Enter third value: ";
        c = getValidNumber<int>();
        std::cout << "Max value: " << findMax(a, b, c) << std::endl;
    } else if (choice == 2) {
   
        std::string a, b, c;
        std::cout << "Enter first value: ";
        std::getline(std::cin, a);
        trim(a); 
        std::cout << "Enter second value: ";
        std::getline(std::cin, b);
        trim(b); 
        std::cout << "Enter third value: ";
        std::getline(std::cin, c);
        trim(c); 

        if (a.empty() || b.empty() || c.empty()) {
            std::cout << "Error: Input strings cannot be empty." << std::endl;
        } else {
            std::cout << "Max value: " << findMax(a, b, c) << std::endl;
        }
    } else {

        std::cout << "Invalid choice. Please enter 1 or 2." << std::endl;
    }

    return 0;
}