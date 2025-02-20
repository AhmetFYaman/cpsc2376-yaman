#include "Validation.h"
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> nums;
    
    printCharByChar("Enter number of integers to input: ");
    int count = getValidNumber<int>(0, 1000);
    
    for (int i = 0; i < count; ++i) {
        printCharByChar("Enter integer #" + std::to_string(i+1) + ": ");
        nums.push_back(getValidNumber<int>());
    }

    auto [min_it, max_it] = std::minmax_element(nums.begin(), nums.end());
    printCharByChar("Smallest element: " + std::to_string(*min_it) + "\n");
    printCharByChar("Largest element: " + std::to_string(*max_it) + "\n");

    return 0;
}