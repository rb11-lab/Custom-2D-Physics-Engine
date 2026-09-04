#pragma once
#include <vector>
#include <cmath>
#include "Circle.h"
#include "Physics.h"

class World {
public:
    std::vector<Circle> circles;
    float simulationTime = 0.0f;
    float totalEnergy = 0.0f;
    float drag = 0.05f;
    float width = 800.0f;
    float height = 600.0f;

    World(float w = 800.0f, float h = 600.0f) : width(w), height(h) {}

    // Adding a new circle to the world
    void AddCircle(const Circle& circle) {
        circles.push_back(circle);
    }

    // Physics update method for one frame (dt)
    void Update(float dt) {
        // Counting simulation time
        simulationTime += dt;

        // Moving all circles, handling wall collisions, and air resistance
        for (auto& circle : circles) {
            Physics::PositionAfterMoving(circle, dt);
            Physics::HandleWallCollisions(circle, width, height, 0.95f);
            Physics::AirResistance(circle, drag, dt);
        }

        // N-body collision resolution (checking every unique pair)
        for (size_t i = 0; i < circles.size(); ++i) {
            for (size_t j = i + 1; j < circles.size(); ++j) {
                Circle& a = circles[i];
                Circle& b = circles[j];
                float collisionTime;

                if (Physics::IsColliding(a, b, dt, collisionTime))
                {
                    // If there was collision calculate accurate impulse            
                    Vec2 normal = Physics::NormalizedVector(a.position, b.position); 
                    float velocityAlongNormal = Physics::VelocityAlongNormal(a, b, normal);

                    // If they are moving closer, impulse should be applied
                    if (velocityAlongNormal < 0) {
                        Vec2 J = Physics::Impulse(a, b, normal, velocityAlongNormal, 0.98f);
                        a.velocity -= J * a.invMass();
                        b.velocity += J * b.invMass();
                    }
                }
            }
        }

        // Calculating total kinetic energy at the end of the frame
        totalEnergy = 0.0f;
        for (const auto& c : circles) {
            float vSq = c.velocity.x * c.velocity.x + c.velocity.y * c.velocity.y;
            totalEnergy += 0.5f * c.mass * vSq;
        }
    }
};