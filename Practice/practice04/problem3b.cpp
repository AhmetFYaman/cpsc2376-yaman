#include "ValidationPro.h"
#include <iostream>
#include <deque>
#include <string>


int displayMenu() {
    std::cout << "\n1. Add Text\n";
    std::cout << "2. Undo Last Edit\n";
    std::cout << "3. Show Content\n";
    std::cout << "4. Exit\n";
    std::cout << "Choice: ";
    return getValidNumber<int>(1); 
}

int main() {
    std::deque<std::string> textEdits; 
    int choice = 0;

    while (choice != 4) { 
        choice = displayMenu(); 

        if (choice == 1) { 
            std::string text;
            std::cout << "Enter text: ";
            std::getline(std::cin, text);
            trim(text); 

            if (!text.empty()) {
                textEdits.push_back(text); 
                std::cout << "Text added!\n";
            } else {
                std::cout << "Error: Text cannot be empty.\n";
            }
        } else if (choice == 2) { 
            if (textEdits.empty()) {
                std::cout << "No edits to undo.\n";
            } else {
                textEdits.pop_back(); 
                std::cout << "Undo successful!\n";
            }
        } else if (choice == 3) { 
            if (textEdits.empty()) {
                std::cout << "Current Content: (empty)\n";
            } else {
                std::cout << "Current Content: ";
                for (const auto& text : textEdits) {
                    std::cout << text << " ";
                }
                std::cout << "\n";
            }
        } else if (choice == 4) { 
            std::cout << "Exiting program. Goodbye!\n";
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}