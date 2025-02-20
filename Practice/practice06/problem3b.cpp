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

    printCharByChar("Enter threshold value: ");
    int threshold = getValidNumber<int>();
    
    int count_above = std::count_if(nums.begin(), nums.end(),
        [threshold](int x) { return x > threshold; });
    printCharByChar("Elements above threshold: " + std::to_string(count_above) + "\n");

    auto new_end = std::remove_if(nums.begin(), nums.end(),
        [threshold](int x) { return x <= threshold; });
    nums.erase(new_end, nums.end());

    printCharByChar("Filtered list: ");
    for (int x : nums) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}