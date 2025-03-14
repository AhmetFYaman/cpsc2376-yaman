#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
//AI note: asked for the simplest and most concise way to get a line of space separated numbers from the user, and put them in a vector
// AI note: got help for the sorter lambda
// PS: the instructions were to order them as in all the odd numbers are larger than even numbers but never specified whether we should put them first or last as in in decending to even or accending to odd, so I went with the example code and when with the deccending order order, odd first even last
int main() {

    std::cout << "Enter int numbers separated by space: ";
    std::string input;
    std::getline(std::cin, input);

 
    std::vector<int> numbers;
    std::istringstream iss(input);
    int num;
    while (iss >> num) {
        numbers.push_back(num);
    }


    std::sort(numbers.begin(), numbers.end(), [](int a, int b) {

        bool a_is_odd = a % 2 != 0;
        bool b_is_odd = b % 2 != 0;

        if (a_is_odd && !b_is_odd) {
            return true;
        } else if (!a_is_odd && b_is_odd) {
            return false; 
        } else if (a_is_odd && b_is_odd) {
            
            return a > b;
        } else {
            
            return a > b;
        }
    });

    std::cout << "Sorted Output: ";
    for (const auto& n : numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    return 0;
}