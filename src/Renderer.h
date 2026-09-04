#pragma once
#include <SDL3/SDL.h>
#include "Circle.h"

void DrawCircle(SDL_Renderer* renderer, const Circle& circle) {
    float PI = 3.14159265f;
    for (int deg = 0; deg < 360; ++deg) {
        float rad = deg * (PI / 180); // Converting degrees to radians

        float x = circle.position.x + circle.r * cos(rad);
        float y = circle.position.y + circle.r * sin(rad);
        
        SDL_RenderPoint(renderer, x, y);
    }
}