#include "../include/Coordinates.hpp"

Coordinates::Coordinates() : x(0.0f), y(0.0f) {}

Coordinates::Coordinates(float xVal, float yVal) : x(xVal), y(yVal) {}

float Coordinates::getX() const {
    return x;
}

float Coordinates::getY() const {
    return y;
}

void Coordinates::setX(float xVal) {
    x = xVal;
}

void Coordinates::setY(float yVal) {
    y = yVal;
}

void Coordinates::setPosition(float xVal, float yVal) {
    x = xVal;
    y = yVal;
}

Coordinates Coordinates::operator+(const Coordinates& other) const {
    return Coordinates(x + other.x, y + other.y);
}

bool Coordinates::operator==(const Coordinates& other) const {
    return (x == other.x) && (y == other.y);
}