#include <iostream>
#include <string>
#include <limits>
#include <sstream>
#include <deque>
#include <vector>
#include <list>
#include <unordered_map>

template<typename T>
T add(T a, T b) {
    return a + b;
}
template<typename T>
T getInput(std::string prompt){

    while (true) {
        std::cout << prompt;
        T output;
        std::cin >> output;
        if (std::cin.fail() || std::cin.peek() != '\n') {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please try again.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return output;
        }
    }
    std::cout << prompt;
    T output;
    std::cin >> output;
    return output;
}

 
int main() { 



    // std::list<int> nums;
    // nums.push_back(23);
    // nums.push_front(99);
    // std::cout << nums.at(0) << "/n";

    // for (int num : nums){
    //     std::cout << num << "/n";
    // }
    // std::cout << "\n";


    std::unordered_map<int, int> squareLookup;
    squareLookup[4] = 16;
    squareLookup[3] = 9;
    squareLookup[8] = 64;
    std::cout << squareLookup.at(3) << "\n";
    std::cout << squareLookup[8] << "\n"; 
}
