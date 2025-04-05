#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <cmath>
#include <iomanip>

// Used Claude AI to perfectionize the code and fix bugs

class Shape {
public:
    virtual double getArea() const = 0;
    virtual ~Shape() = default; 
};


class Rectangle : public Shape {
private:
    double width;
    double height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    
    double getArea() const override {
        return width * height;
    }
};


class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    
    double getArea() const override {
        return M_PI * radius * radius;
    }
};

void printAllAreas(const std::vector<std::unique_ptr<Shape>>& shapes) {
    for (const auto& shape : shapes) {
        std::cout << "Area: " << std::fixed << std::setprecision(4) << shape->getArea() << std::endl;
    }
}

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    std::ifstream file("shapes.txt");
    
    if (!file) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }
    
    std::string shapeType;
    while (file >> shapeType) {
        if (shapeType == "rectangle") {
            double width, height;
            file >> width >> height;
            shapes.push_back(std::make_unique<Rectangle>(width, height));
        } 
        else if (shapeType == "circle") {
            double radius;
            file >> radius;
            shapes.push_back(std::make_unique<Circle>(radius));
        }
        else {
            std::cerr << "Unknown shape type: " << shapeType << std::endl;
        }
    }
    

    printAllAreas(shapes);
    

    return 0;
}