#include "Vector2.h"

#include <math.h>

Vector2::Vector2()
: x(0)
, y(0) {
};

Vector2::Vector2(const float x, const float y)
: x(x)
, y(y) {
};

Vector2::Vector2(const int x, const int y)
: x(static_cast<float>(x))
, y(static_cast<float>(y)) {
};

Vector2 Vector2::operator + (const Vector2& v) const {
    return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator - (const Vector2& v) const {
    return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator * (const float t) const {
    return Vector2(x * t, y * t);
}

Vector2 Vector2::operator / (const float t) const {
    return *this * (1.0f / t);
}

Vector2 Vector2::operator - () const {
    return Vector2(-x, -y);
}

bool Vector2::operator == (const Vector2& v) const {
    return ((x == v.x) && (y == v.y));
}

bool Vector2::operator != (const Vector2& v) const {
    return !(*this == v);
}

void Vector2::operator += (const Vector2& v) {
    *this = *this + v;
}

void Vector2::operator -= (const Vector2& v) {
    *this = *this - v;
}

float Vector2::sqrMagnitude() {
    return x * x + y * y;
}

float Vector2::magnitude() {
    return sqrt(this->sqrMagnitude());
}

Vector2 Vector2::normalized() {
    return *this / this->magnitude();
}

Vector2 Vector2::zero = Vector2(0, 0);
Vector2 Vector2::one = Vector2(1, 1);
Vector2 Vector2::left = Vector2(-1, 0);
Vector2 Vector2::right = Vector2(1, 0);
Vector2 Vector2::down = Vector2(0, -1);
Vector2 Vector2::up = Vector2(0, 1);
