#include "Physics.h"
#include <cmath>

namespace Physics {
    bool IsColliding(const Circle& a, const Circle& b, float dt, float &outTime) {
        // D = R -> The point of collision 
        float R = a.r + b.r;

        // Calculating relative speed | Vrel = Vb - Va
        float dVx = (b.velocity.x - a.velocity.x) * dt;
        float dVy = (b.velocity.y - a.velocity.y) * dt;

        // Vector from A to B | D = (dx, dy)
        float dx = b.position.x - a.position.x;
        float dy = b.position.y - a.position.y;

        // D(t) = D + V*t | D -> B relatively to A | V -> relative speed | D + V*t -> B relatively to A through t

        // D = R -> D(t) = R -> D(t)^2 = R^2 -> (D + V*t)^2 = R^2
        // ((dx, dy) + (dVx, dVy)*t)^2 = R ^2 -> (dx + dVx*t)^2 + (dy + dVy*t)^2 = R^2 ->
        // -> dx^2 + 2dx*dVx*t + dVx^2*t^2 + dy^2 + 2dy*dVy*t + dVy^2*t^2 = R^2
        // -> (dVx^2 + dVy^2)*t^2 + 2(dx * dVx + dy * dVy)*t + (dx^2 + dy^2 - R^2) = 0
        
        // A = dVx^2 + dVy^2 | B = 2(dx * dVx + dy * dVy) | C = (dx^2 + dy^2) - R^2
        // A = ΔPrel^2​ -> ΔPrel = Vrel*dt, which is relative displacement during timestep
        float A = dVx * dVx + dVy * dVy;
        float B = 2.0f * (dx * dVx + dy * dVy);
        float C = (dx * dx + dy * dy) - (R * R);

        // (dx^2 + dy^2) = D^2 | D^2 - R^2 <= 0 | D^2 <= R^2 | D <= R ---> Circles collide
        if (C <= 0) {
            outTime = 0.0f;
            return true;
        }

        constexpr float epsilon = 0.000001f;

        if (A < epsilon) return false;

        float D = B * B - 4.0f * A * C;
        
        // No roots = No collision
        if (D < 0) return false;

        else if (D >= 0) {
            // t1 is entry point and t2 is exit point, for that reason I use t1
            float t = (-B - sqrt(D)) / (2.0f * A);

            // t is the part of the current physics step where 0 is the start and 1 is the end
            // The step = 0.016s and if the t = 0.5 ---> 0.5 * 0.016s = 0.008s
            // Which means the collision happened 8 milliseconds after the start of the current physics step
            if (t >= 0.0f && t <= 1.0f) {
                outTime = t;
                return true;
            }

            return false;
        }

        return false;
    }

    void PositionAfterMoving(Circle& a, float dt) {
        a.position += a.velocity * dt;
    }

    Vec2 NormalizedVector(const Vec2 &a, const Vec2 &b) {
        Vec2 V = b - a;

        return V.Normal();
    }

    float VelocityAlongNormal(const Circle &a, const Circle &b, const Vec2 &normal) {
        Vec2 relativeVelocity = b.velocity - a.velocity; // B relative to A
        float velocityAlongNormal = relativeVelocity.Dot(normal);

        return velocityAlongNormal;
    }

    Vec2 Impulse(const Circle &a, const Circle &b, Vec2 &normal, const float vn, float e) {
        float factor = -(1.0f + e) / (a.invMass() + b.invMass());
        float impulse = vn * factor;

        return normal * impulse;
    }

    void HandleWallCollisions(Circle &a, float windowWidth, float windowHeight, float elasticity) {
        // Left wall
        if (a.position.x - a.r <= 0.0f) {
            a.position.x = a.r;                 // Return to the boundary
            a.velocity.x *= -elasticity; // Reverse and dampen the velocity
        }
        // Right wall
        if (a.position.x + a.r >= windowWidth) {
            a.position.x = windowWidth - a.r;
            a.velocity.x *= -elasticity;
        }
        // Top wall
        if (a.position.y - a.r <= 0.0f) {
            a.position.y = a.r;
            a.velocity.y *= -elasticity;
        }
        // Bottom wall
        if (a.position.y + a.r >= windowHeight) {
            a.position.y = windowHeight - a.r;
            a.velocity.y *= -elasticity;
        }
    }

    void AirResistance(Circle &a, float drag, float dt) {
        a.velocity *= 1.0f - drag * dt;
    }
}