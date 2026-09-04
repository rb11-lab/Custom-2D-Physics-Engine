#pragma once
#include "Vec2.h"
#include <cstdint>

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

struct Circle {
    Vec2 position;
    Vec2 velocity;
    float r;
    float mass;
    Color color;

    float invMass() const {
        return mass > 0.0f ? 1.0f / mass : 0.0f;
    }
};