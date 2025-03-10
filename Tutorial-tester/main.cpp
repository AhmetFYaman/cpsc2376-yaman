#include <iostream>
 
class Animal {
public:
    virtual void speak() = 0;  // Pure virtual function
    virtual ~Animal() = default;
};
 
class Cat : public Animal {
public:
    void speak() override { std::cout << "Meow"; }
};
 
std::ostream& operator<<(std::ostream& os, Animal& a) {
    a.speak();
    return os;
}
 
int main() {
    Cat c;
    std::cout << c << std::endl;  // Prints "Meow"
}
 