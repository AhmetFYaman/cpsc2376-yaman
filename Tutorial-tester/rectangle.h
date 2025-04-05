// rectangle.h
#pragma once
#include <iostream>
 
class Rectangle {
public:
    Rectangle(int w, int h) : width(w), height(h) {
        std::cout << "Rectangle constructed: " << width << "x" << height << std::endl;
    }
    ~Rectangle() {
        std::cout << "Rectangle destructed: " << width << "x" << height << std::endl;
    }
    void printArea() const {
        std::cout << "Area: " << width * height << std::endl;
    }
private:
    int width;
    int height;
};
 