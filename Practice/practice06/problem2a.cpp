#include "Validation.h"
#include <vector>
#include <numeric>
#include <functional>

int main() {
    std::vector<int> nums;
    
    printCharByChar("Enter number of integers to input: ");
    int count = getValidNumber<int>(0, 1000);
    
    for (int i = 0; i < count; ++i) {
        printCharByChar("Enter integer #" + std::to_string(i+1) + ": ");
        nums.push_back(getValidNumber<int>());
    }

    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    printCharByChar("Sum: " + std::to_string(sum) + "\n");

    int product = std::accumulate(nums.begin(), nums.end(), 1, std::multiplies<int>());
    printCharByChar("Product: " + std::to_string(product) + "\n");

    return 0;
}