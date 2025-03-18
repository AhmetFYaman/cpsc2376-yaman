#include <iostream>
#include <array>
 
int main() {
    std::array<int, 5> arr = {1, 2, 3, 4, 5};
    
    // Pointer to the first element of arr
    int* p = arr.data();
    std::cout << "Initial pointer p: " << p
              << " | *p: " << *p << std::endl;
    
    // Move pointer to the next element
    p++;
    std::cout << "After p++: " << p
              << " | *p: " << *p << std::endl;
    
    // Move pointer two more elements
    p += 2;
    std::cout << "After p += 2: " << p
              << " | *p: " << *p << std::endl;
    std::cout<< *p;
 
    return 0;
}