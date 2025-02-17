#include <iostream>
#include "Validation.h" // Include the professional input validation header

// Function to convert temperature
std::string greet(std::string name = "Guest", std::string prefix = "Hello") {
    return prefix + " " + name + "!";

}


int main() {
    int choice = 0; 


    //while (choice != 4) {

        std::cout << "Greeting System, Select a choice:" << std::endl;
        std::cout << "1. Default Greeting" << std::endl;
        std::cout << "2. Greet by Name" << std::endl;
        std::cout << "3. Custom Greeting" << std::endl;
        std::cout << "4. Exit" << std::endl;
        choice = getValidInteger(); 

        if (choice == 1) {

            std::cout << greet() << std::endl;
        } else if (choice == 2) {
            std::cout << "Enter your name: ";
            std::string name = getValidString();
            std::cout << greet(name) << std::endl;
        } else if (choice == 3) {
            std::cout << "Enter your name: ";
            std::string name = getValidString();
            std::cout << "Enter a prefix: ";
            std::string prefix = getValidString();
            std::cout << greet(name, prefix) << std::endl;

        } else if (choice == 4) {
            std::cout << "Exiting the program." << std::endl;
        
        }else {
            std::cout << "Invalid choice. Please try again." << std::endl;

        }

    
    //}
    return 0;
}