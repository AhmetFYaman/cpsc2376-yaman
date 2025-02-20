#include "Validation.h"
#include <vector>

int main() {
    std::vector<int> nums;
    
    printCharByChar("Enter number of integers to input: ");
    int count = getValidNumber<int>(0, 1000);
    
    for (int i = 0; i < count; ++i) {
        printCharByChar("Enter integer #" + std::to_string(i+1) + ": ");
        nums.push_back(getValidNumber<int>());
    }

    printCharByChar("Reverse order: ");
    for (auto rit = nums.rbegin(); rit != nums.rend(); ++rit) {
        std::cout << *rit << " ";
    }
    std::cout << "\n";

    return 0;
}