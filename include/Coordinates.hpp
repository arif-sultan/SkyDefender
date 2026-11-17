#ifndef COORDINATES_HPP
#define COORDINATES_HPP

#include <iostream>
using namespace std;

class Coordinates {
private:
    float x;
    float y;

public:
    // Default and Parameterized Constructors
    Coordinates();
    Coordinates(float xVal, float yVal);

    // Const-correct Getters
    float getX() const;
    float getY() const;

    // Setters
    void setX(float xVal);
    void setY(float yVal);
    void setPosition(float xVal, float yVal);

    // Operator Overloading (OOP Requirement B.3)
    Coordinates operator+(const Coordinates& other) const;
    bool operator==(const Coordinates& other) const;
};

#endif