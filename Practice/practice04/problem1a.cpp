#include <iostream>
#include "Validation.h" 

// Function to convert temperature
double convertTemperature(double temp, char scale = 'F') {
    if (scale == 'F' || scale == 'f') {
        return (temp - 32) * 5 / 9;
    } else if (scale == 'C' || scale == 'c') {
        return (temp * 9 / 5) + 32;
    } else {
        std::cout << "Invalid scale entered. Please use 'F' or 'C'." << std::endl;
        return 0.0;
    }
}

int main() {
    int choice = 0; 
    double temperature;

    //while (choice != 3) {

        std::cout << "Temperature Conversion Menu" << std::endl;
        std::cout << "1. Convert Fahrenheit to Celsius" << std::endl;
        std::cout << "2. Convert Celsius to Fahrenheit" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        choice = getValidInteger(); 

        if (choice == 1) {
            std::cout << "Enter temperature in Fahrenheit: ";
            temperature = getValidDouble(); 
            double celsius = convertTemperature(temperature, 'F');
            std::cout << temperature << " Fahrenheit is " << celsius << " Celsius." << std::endl;
        } else if (choice == 2) {
            std::cout << "Enter temperature in Celsius: ";
            temperature = getValidDouble();
            double fahrenheit = convertTemperature(temperature, 'C');
            std::cout << temperature << " Celsius is " << fahrenheit << " Fahrenheit." << std::endl;
        } else if (choice == 3) {
            std::cout << "Exiting the program." << std::endl;
        } else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    //}

    return 0;
}