#include "ValidationPro.h"
#include <algorithm> // Ig not needed since ValidationPro.h includes it
#include <iostream> // Ig not needed since ValidationPro.h includes it
// Organization of code, enhancing of user flexibility, the implementation of the new getValidString and toLower functions and enhancing them was done
// using claude AI
// The base of the code (code that meets the requirements but has some bugs and isnt flashy), the logic, and the intstructions of how it should be organized done by me 

float redPotion{0.0f};    // Amount of red potion in mL
float bluePotion{0.0f};   // Amount of blue potion in mL
float* flask{nullptr};    // Pointer to the selected potion

int main() {
    // Prompt the user to select a potion
    std::string potion{""};
    
    printCharByChar("Welcome to the Potion Mixing Program!\n\n");
    
    while(potion != "done"){
        printCharByChar("\n---------------------------\n");
        printCharByChar("Type 'done' to exit the program\n");
        printCharByChar("Select a potion (red or blue): ");
        
        potion = getValidSingleWord("red", "blue", "done");

        if(potion == "done"){
            printCharByChar("\nExiting program. Thank you for using Potion Mixer!\n");
            break;
        }


        if (potion == "red") {
            flask = &redPotion;
            printCharByChar("\nRed potion selected. ");
        } else if (potion == "blue") {
            flask = &bluePotion;
            printCharByChar("\nBlue potion selected. ");
        }
    
    
        printCharByChar("Pour the potion (0.0 mL - 100.0 mL): ");
        float amountToPour = getValidNumber<float>(0.0f, 100.0f);
        
        *flask += amountToPour;
        std::string message = "\nYou poured " + std::to_string(amountToPour) + " mL of " + potion + " potion.\n";
        printCharByChar(message);
   
        std::string totals = "Current totals: Red: " + std::to_string(redPotion) + 
                            " mL, Blue: " + std::to_string(bluePotion) + " mL\n";
        printCharByChar(totals);
    }
    
    return 0;
}