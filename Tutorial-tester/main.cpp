#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <chrono>
 
 
int main() {
    const int N = 100'000;
    
    std::vector<int> v;
    std::list<int> l;
    std::deque<int> d;
 
 
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) v.insert(v.begin(), i); //vector doesn't have push_front but this is functionally the same
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Vector: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";
 
 
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) l.push_front(i);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "List: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";
 
 
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) d.push_front(i);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Deque: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";
 
 
    return 0;
}