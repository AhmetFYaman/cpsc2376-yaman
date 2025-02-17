#include "ValidationPro.h"
#include <iostream>
#include <list>
#include <string>


int displayMenu() {
    std::cout << "\n1. Add Task\n";
    std::cout << "2. Remove Task\n";
    std::cout << "3. Show Tasks\n";
    std::cout << "4. Exit\n";
    std::cout << "Choice: ";
    return getValidNumber<int>(1); 
}

int main() {
    std::list<std::string> tasks; 
    int choice = 0;

    while (choice != 4) {
        choice = displayMenu(); 

        if (choice == 1) { 
            std::string task;
            std::cout << "Enter task: ";
            std::getline(std::cin, task);
            trim(task);

            if (!task.empty()) {
                tasks.push_back(task); 
                std::cout << "Task added!\n";
            } else {
                std::cout << "Error: Task cannot be empty.\n";
            }
        } else if (choice == 2) { 
            if (tasks.empty()) {
                std::cout << "No tasks to remove.\n";
            } else {
                
                std::cout << "Tasks:\n";
                int index = 1;
                for (const auto& task : tasks) {
                    std::cout << index++ << ". " << task << "\n";
                }

                
                std::cout << "Enter task number to remove: ";
                int taskNumber = getValidNumber<int>(1); 

                if (taskNumber > 0 && taskNumber <= tasks.size()) {
                    auto it = tasks.begin();
                    std::advance(it, taskNumber - 1); 
                    tasks.erase(it); 
                    std::cout << "Task removed!\n";
                } else {
                    std::cout << "Error: Invalid task number.\n";
                }
            }
        } else if (choice == 3) { 
            if (tasks.empty()) {
                std::cout << "No tasks to display.\n";
            } else {
                std::cout << "Tasks:\n";
                int index = 1;
                for (const auto& task : tasks) {
                    std::cout << index++ << ". " << task << "\n";
                }
            }
        } else if (choice == 4) { // Exit
            std::cout << "Exiting program. Goodbye!\n";
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}