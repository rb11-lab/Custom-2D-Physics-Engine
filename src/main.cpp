#include <iostream>
#include <cmath>
#include <SDL3/SDL.h>
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include "Physics.h"
#include "Renderer.h"
#include "World.h"

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) == false) {
        std::cout << "SDL Init Error: " << SDL_GetError() << "\n";
        return -1; // Closing the app if met with error
    }

    SDL_Window* window = SDL_CreateWindow("Physics Engine", 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    World world;

    Circle a;
    a.position = {100.0f, 300.0f};
    a.r = 30.0f;
    a.velocity = {100.0f, 20.0f};
    a.mass = 10.0f;
    a.color = {255, 75, 75, 255}; // Red
    world.AddCircle(a);

    Circle b;
    b.position = {700.0f, 300.0f};
    b.r = 30.0f;
    b.velocity = {-150.0f, 30.0f};
    b.mass = 1.0f;
    b.color = {75, 150, 255, 255}; // Blue
    world.AddCircle(b);

    float dt = 0.016f;
    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        // Reading events (INPUT)
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT) {
                isRunning = false; // If closed the window - leaving cycle
            }
        }

        float mouseX, mouseY;
        Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

        // Проверяем, зажата ли левая кнопка мыши
        if (mouseState & SDL_BUTTON_MASK(SDL_BUTTON_LEFT)) {
            // Проходим по всем шарам в мире
            for (auto& circle : world.circles) {
                float dx = mouseX - circle.position.x;
                float dy = mouseY - circle.position.y;
                float distSq = dx * dx + dy * dy;

                // Если кликнули внутри радиуса шара
                if (distSq <= circle.r * circle.r) {
                    // Придаем шару ускорение в сторону курсора (или резкий пинок)
                    circle.velocity += Vec2{dx * 2.0f, dy * 2.0f};
                }
            }
        }

        // Updating the entire physics in one line
        world.Update(dt);

        // UI ImGui
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        // Creating the degub window
        ImGui::Begin("Physics Inspector");

        // Spawn button
        if (ImGui::Button("Spawn Random Ball")) {
            Circle newCircle;

            // Random position within safe screen area
            float rx = static_cast<float>((rand() % 600) + 100);
            float ry = static_cast<float>((rand() % 400) + 100);
            newCircle.position = {rx, ry};

            float vx = static_cast<float>((rand() % 300) - 150);
            float vy = static_cast<float>((rand() % 300) - 150);
            newCircle.velocity = {vx, vy};
            
            newCircle.r = 20.0f + static_cast<float>(rand() % 15);
            newCircle.mass = newCircle.r * 0.2f; // Mass scales with radius
            
            uint8_t rc = static_cast<uint8_t>(rand() % 180 + 75);
            uint8_t gc = static_cast<uint8_t>(rand() % 180 + 75);
            uint8_t bc = static_cast<uint8_t>(rand() % 180 + 75);
            newCircle.color = {rc, gc, bc, 255};

            world.AddCircle(newCircle);
        }

        ImGui::Text("Total Circles: %zu", world.circles.size());
        ImGui::Separator();
        
        // Printing the dynamic info
        // Dynamic loop for all circles in the world
        for (size_t i = 0; i < world.circles.size(); ++i) {
            ImGui::Text("Ball %zu Pos: (%.1f, %.1f)", i, world.circles[i].position.x, world.circles[i].position.y);
            ImGui::Text("Ball %zu Vel: (%.1f, %.1f)", i, world.circles[i].velocity.x, world.circles[i].velocity.y);
            ImGui::Separator();
        }
        
        ImGui::Text("Total Kinetic Energy: %.1f J", world.totalEnergy);
        ImGui::Separator();
        ImGui::Text("Simulation Time: %.2f s", world.simulationTime);

        ImGui::End(); // Closing the window
        
        ImGui::Render();

        // Rendering the dark-grey screen
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); 
        SDL_RenderClear(renderer);

        // Drawing all balls throught the cycle
        for (const auto& circle : world.circles) {
            // Each circle has individual color
            SDL_SetRenderDrawColor(renderer, circle.color.r, circle.color.g, circle.color.b, circle.color.a);

            // Fuction to draw circle
            DrawCircle(renderer, circle);
        }

        // Drawing GI over the balls
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);

        // Showing the complete frame on the screen
        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}