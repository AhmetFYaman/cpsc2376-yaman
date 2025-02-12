        OLD                                                            NEW?UPDATE



static int sumRange(int start, int end) {
    int sum = 0;
    for (int i = start; i < end; i++) {                  -->           for (int i = start; i <= end; i++) { 
        sum += i;
    }
    return sum;
}




static bool containsNegative(const std::vector<int>& numbers) {
    for (size_t i = 0; i <= numbers.size(); i++) {             -->   for (size_t i = 0; i < numbers.size(); i++) {      
        if (numbers[i] > 0) {                             -->         if (numbers[i] < 0) {    
            return true;
        }
    }
    return false;
}




#include <climits> // For INT_MIN

static int findMax(const std::vector<int>& numbers) {
    if (numbers.empty()) {
        return 0;                                             --> throw std::invalid_argument("Input vector is empty");
    }
    int maxVal = numbers[0];
    for (size_t i = 1; i <= numbers.size(); i++) {         -->    for (size_t i = 1; i < numbers.size(); i++) { 
        if (numbers[i] >= maxVal) {                        -->    if (numbers[i] > maxVal) { 
            maxVal = numbers[i];
        }
    }
    return maxVal;
}
