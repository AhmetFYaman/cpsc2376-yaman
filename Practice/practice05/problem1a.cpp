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

    printCharByChar("Elements: ");
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    int even_sum = 0;      
    for (auto it = nums.begin(); it != nums.end(); ++it) {   // I think using accumulate() would be cooler but its an algorithm, lets keep it for algorithm part
        if (*it % 2 == 0) even_sum += *it;   
    }
    printCharByChar("Sum of even numbers: " + std::to_string(even_sum) + "\n");

    return 0;
}