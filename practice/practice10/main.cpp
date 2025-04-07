#include <fstream>
#include <vector>
#include <memory>
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>

class Shape {
public:
    virtual double getArea() const = 0;
    virtual ~Shape() = default;
};

class Rectangle : public Shape {
    double width;
    double height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double getArea() const override {
        return width * height;
    }
};

class Circle : public Shape {
    double radius;
public:
    Circle(double r) : radius(r) {}
    double getArea() const override {
        return 3.14159 * radius * radius;
    }
};

void printAllAreas(const std::vector<std::unique_ptr<Shape>>& shapes) {
    for (const auto& shape : shapes) {
        double area = shape->getArea();
        if (area == static_cast<long long>(area)) {
            std::cout << "Area: " << static_cast<long long>(area) << '\n';
        } else {
            std::cout << "Area: " << std::fixed << std::setprecision(4) << area << '\n';
            std::cout.unsetf(std::ios::fixed);
            std::cout << std::setprecision(6);
        }
    }
}

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    const std::string filename = "shapes.txt";  // Hardcoded filename

    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Could not open file: " << filename << "\n";
        std::cerr << "Make sure 'shapes.txt' exists in the program's directory.\n";
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;
        if (type == "rectangle") {
            double width, height;
            if (iss >> width >> height) {
                shapes.push_back(std::make_unique<Rectangle>(width, height));
            } else {
                std::cerr << "Invalid rectangle data in line: " << line << '\n';
            }
        } else if (type == "circle") {
            double radius;
            if (iss >> radius) {
                shapes.push_back(std::make_unique<Circle>(radius));
            } else {
                std::cerr << "Invalid circle data in line: " << line << '\n';
            }
        } else {
            std::cerr << "Unknown shape type: " << type << " in line: " << line << '\n';
        }
    }

    printAllAreas(shapes);
    return 0;
}