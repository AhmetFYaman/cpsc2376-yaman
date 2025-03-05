#include <iostream>
#include "Fraction.cpp"
#include "MixedFraction.cpp"
#include "ValidationPro.h"

void displayMenu(const Fraction& currentFraction) {
    std::cout << "\nCurrent Fraction: " << currentFraction << std::endl;
    std::cout << "Options:\n"
              << "1. Enter a fraction manually\n"
              << "2. Add a fraction\n"
              << "3. Subtract a fraction\n"
              << "4. Multiply by a fraction\n"
              << "5. Divide by a fraction\n"
              << "6. Display as Mixed Fraction\n"
              << "7. Clear Fraction\n"
              << "8. Exit\n"
              << "Choose an option: ";


}

Fraction enterFractionManually() {
    std::cout << "Enter numerator: ";
    int numerator = getValidNumber<int>();

    std::cout << "Enter denominator (cannot be zero): ";
    int denominator = getValidNumber<int>(1, std::numeric_limits<int>::max());

    return Fraction(numerator, denominator);
}

Fraction performOperation(const Fraction& currentFraction, const std::string& operation) {
    std::cout << "Enter numerator for the second fraction: ";
    int numerator = getValidNumber<int>();

    std::cout << "Enter denominator for the second fraction (cannot be zero): ";
    int denominator = getValidNumber<int>(1, std::numeric_limits<int>::max());

    Fraction secondFraction(numerator, denominator);

    if (operation == "add") {
        return currentFraction + secondFraction;
    } else if (operation == "subtract") {
        return currentFraction - secondFraction;
    } else if (operation == "multiply") {
        return currentFraction * secondFraction;
    } else if (operation == "divide") {
        return currentFraction / secondFraction;
    }

    throw std::invalid_argument("Invalid operation.");
}


int main() {
    Fraction currentFraction;
    bool running = true;

    while (running) {
        displayMenu(currentFraction);
        int choice = getValidNumber<int>(1, 8);

        if (choice == 1) {
            currentFraction = enterFractionManually();
        } else if (choice == 2) {
            currentFraction = performOperation(currentFraction, "add");
        } else if (choice == 3) {
            currentFraction = performOperation(currentFraction, "subtract");
        } else if (choice == 4) {
            currentFraction = performOperation(currentFraction, "multiply");
        } else if (choice == 5) {
            currentFraction = performOperation(currentFraction, "divide");
        } else if (choice == 6) {
            MixedFraction mixed(currentFraction);
            std::cout << "Mixed Fraction: " << mixed << std::endl;
        } else if (choice == 7) {
            currentFraction = Fraction(); // Reset to 0/1
            std::cout << "Fraction cleared.\n";
        } else if (choice == 8) {
            running = false;
            std::cout << "Exiting program.\n";
        } else {
            std::cout << "Invalid choice. Try again.\n";
        }

    }

    return 0;
}