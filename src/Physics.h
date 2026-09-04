#pragma once
#include "Circle.h"
#include "Vec2.h"

namespace Physics {
    bool IsColliding(const Circle& a, const Circle& b, float dt, float &outTime);
    void PositionAfterMoving(Circle& a, float dt);
    Vec2 NormalizedVector(const Vec2 &a, const Vec2 &b);
    float VelocityAlongNormal(const Circle &a, const Circle &b, const Vec2 &normal);
    Vec2 Impulse(const Circle &a, const Circle &b, Vec2 &normal, const float vn, float e);
    void HandleWallCollisions(Circle &a, float windowWidth, float windowHeight, float elasticity);
    void AirResistance(Circle &a, float drag, float dt);
}