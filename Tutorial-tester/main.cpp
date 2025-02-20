#include <iostream>
#include <vector>
#include <algorithm>
 
int main() {
    std::vector<int> values = {5, 2, 8, 3, 1};
    std::sort(values.begin(), values.end(), [](int a, int b) { return a%2 < b%2; });
    for (int v : values) {
        std::cout << v << " ";
    }
    return 0;
}