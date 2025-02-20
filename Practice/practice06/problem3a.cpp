#include "Validation.h"
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    std::vector<int> nums;
    
    printCharByChar("Enter number of integers to input: ");
    int count = getValidNumber<int>(0, 1000);
    
    for (int i = 0; i < count; ++i) {
        printCharByChar("Enter integer #" + std::to_string(i+1) + ": ");
        nums.push_back(getValidNumber<int>());
    }

    printCharByChar("Squared elements: ");
    std::for_each(nums.begin(), nums.end(), [](int x) { 
        std::cout << x * x << " "; 
    });
    std::cout << "\n";

    int sum_squares = std::accumulate(nums.begin(), nums.end(), 0,
        [](int total, int x) { return total + x * x; });
    printCharByChar("Sum of squares: " + std::to_string(sum_squares) + "\n");

    return 0;
}
