#include "Validation.h"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

void createAccount(const std::string& filename) {
    std::ofstream outFile(filename, std::ios::app);
    double initialBalance = 100.00;
    if (outFile.is_open()) {
        outFile << initialBalance;
        outFile.close();
    } else {
        std::cerr << "Failed to open file for writing." << std::endl;
    }
}

void userMenu(double &accountBalance) {
    printCharByChar("Welcome to your Trusted Bank Account!\n");

    while (true) {
        printCharByChar("What can we do for you today? (enter choice int): \n", 12);
        std::cout << "1: Check Balance " << std::endl;
        std::cout << "2: Deposit " << std::endl;
        std::cout << "3: Withdraw " << std::endl;
        std::cout << "4: Exit " << std::endl;
        int choice;
        choice = getValidInteger();

        if (choice == 1) {
            printCharByChar("Your current balance is: " + std::to_string(accountBalance) + "\n");

        } else if (choice == 2) {
            printCharByChar("How much would you like to deposit? \n", 12);
            double depositAmount = getValidDouble();
            if (depositAmount < 5.00) {
                printCharByChar("Minimum deposit must be greater than the $5.00 fee.\n");
                continue;
            }
            accountBalance += depositAmount - 5.00;  
            printCharByChar("A $5.00 transaction fee has been applied.\n");
            printCharByChar("Your new balance is: $" + std::to_string(accountBalance) + "\n");

        } else if (choice == 3) {
            printCharByChar("How much would you like to withdraw? \n", 12);
            double withdrawAmount = getValidDouble();
            if (withdrawAmount + 5.00 > accountBalance) {
                printCharByChar("Insufficient Funds (including $5.00 fee).\n");
                continue;
            }
            accountBalance -= (withdrawAmount + 5.00);  // Deduct amount + fee
            printCharByChar("A $5.00 transaction fee has been applied.\n");
            printCharByChar("Your new balance is: $" + std::to_string(accountBalance) + "\n");

        } else if (choice == 4) {
            printCharByChar("Thank you for using our services!\n");
            break;

        } else {
            printCharByChar("Invalid Choice\n");
        }
    }
}

void readFileAndUpdate(const std::string& filename) {
    std::ifstream iFile(filename);
    double accountBalance;
    if (!iFile) {
        printCharByChar("No Account Found?!\n");
        printCharByChar("New Check-In Account Creating....\n");
        printCharByChar("New Account with $100.00 has been created.\n");
        printCharByChar("By using this program you agree to the following:\n");
        printCharByChar("Your balance-activity will be tracked and recorded in our database.\n");
        printCharByChar("You will be charged $5.00 for every withdrawal or deposit.\n");
        printCharByChar("Please wait as we process this...\n");
        std::this_thread::sleep_for(std::chrono::seconds(3));

        createAccount("userAccount.txt");
    }
    std::ifstream inFile(filename);
    if (inFile.is_open() || iFile.is_open()) {
        inFile >> accountBalance;
        
        userMenu(accountBalance);

        inFile.close();
        iFile.close();

        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << accountBalance;
            outFile.close();  
            printCharByChar("File updated successfully!\n");
        } else {
            printCharByChar("Error opening file for writing.\n");
        }
        
    } else {
        std::cerr << "Error 404 Not Found." << std::endl;
    }
}

int main() {
    readFileAndUpdate("userAccount.txt");
    return 0;
}
