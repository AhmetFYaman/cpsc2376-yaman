// code refined and perfected using AI
#include <iostream>
#include <vector>
#include "Validation.h"

void displayVector(const std::vector<int>& nums) {
    if (nums.empty()) {
        std::cout << "The vector is empty.\n";
        return;
    }
    std::cout << "Numbers in the vector:\n";
    for (int num : nums) {
        std::cout << num << " ";
    }
    std::cout << "\n";
}

void addNumberToVector(std::vector<int>& nums) {
    std::cout << "Enter a number to add to the vector: ";
    int num = getValidInteger();
    nums.push_back(num);
    std::cout << "Number added successfully!\n";
}

void doubleNumbersInVector(std::vector<int>& nums) {
    if (nums.empty()) {
        std::cout << "The vector is empty. Add numbers first.\n";
        return;
    }
    std::cout << "Doubling all numbers in the vector...\n";
    for (size_t i = 0; i < nums.size(); i++) {
        nums.at(i) *= 2;  
    }
    std::cout << "All numbers have been doubled!\n";
}

void sumVectorNumbers(const std::vector<int>& nums) {
    if (nums.empty()) {
        std::cout << "The vector is empty. No sum to calculate.\n";
        return;
    }
    int sum = 0;
    for (int num : nums) {
        sum += num;
    }
    std::cout << "Total sum of numbers in the vector: " << sum << "\n";
}

void printMultiplesOfValue(const std::vector<int>& nums) {
    if (nums.empty()) {
        std::cout << "The vector is empty. Add numbers first.\n";
        return;
    }
    std::cout << "Enter a number to find its multiples in the vector: ";
    int multiple = getValidInteger();

    std::cout << "Multiples of " << multiple << " in the vector:\n";
    bool found = false;
    for (int num : nums) {
        if (num % multiple == 0) {
            std::cout << num << " ";
            found = true;
        }
    }
    if (!found) {
        std::cout << "No multiples of " << multiple << " found in the vector.";
    }
    std::cout << "\n";
}

int main() {
    std::vector<int> nums; 

    bool running = true;
    while (running) {
        std::cout << "\n===== MENU =====\n";
        std::cout << "1. Display vector\n";
        std::cout << "2. Add a number to the vector\n";
        std::cout << "3. Double numbers in the vector\n";
        std::cout << "4. Calculate sum of the vector\n";
        std::cout << "5. Print multiples of a user-defined value\n";
        std::cout << "6. Exit\n";
        std::cout << "Choose an option: ";

        int choice = getValidInteger();

        if (choice == 1) {
            displayVector(nums);
        } 
        else if (choice == 2) {
            addNumberToVector(nums);
        } 
        else if (choice == 3) {
            doubleNumbersInVector(nums);
        } 
        else if (choice == 4) {
            sumVectorNumbers(nums);
        } 
        else if (choice == 5) {
            printMultiplesOfValue(nums);
        } 
        else if (choice == 6) {
            std::cout << "Exiting program. Goodbye!\n";
            running = false;
        } 
        else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
