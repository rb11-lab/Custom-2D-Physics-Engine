#pragma once
#include <cmath>

struct Vec2 {
    float x;
    float y;

    // Vec2 + Vec2
    Vec2 operator+(const Vec2& other) const {
        return {x + other.x, y + other.y};
    }

    Vec2& operator+=(const Vec2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    // Vec2 * float
    Vec2 operator*(float scalar) const {
        return {x * scalar, y * scalar};
    }

    Vec2& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    // Vec2 - Vec2
    Vec2 operator-(const Vec2& other) const {
        return {x - other.x, y - other.y};
    }

    Vec2& operator-=(const Vec2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    float Length() const {
    return sqrt(x * x + y * y);
    }

    // Dot Product | Vec2 * Vec2
    float Dot(const Vec2& other) const {
        return x * other.x + y * other.y;
    }

    Vec2 Normal() const {
        float len = Length();

        // Protection from Division By Zero
        if (len < 0.0001f) {
            return {0.0f, 0.0f}; // No direction
        }

        return {x / len, y/ len};
    }
};