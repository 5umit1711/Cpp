#include <SDL.h>
#include <cmath>
#include <iostream>

#undef main

const int WIDTH = 800;
const int HEIGHT = 600;
const double G = 0.1; 
const double BLACK_HOLE_MASS = 10000.0;
const double EARTH_MASS = 1.0;
const double DT = 0.01; 
const double BLACK_HOLE_RADIUS = 5.0;
const double EARTH_RADIUS = 5.0;

struct Vector2 {
    double x, y;
    Vector2(double x = 0, double y = 0) : x(x), y(y) {}
    Vector2 operator+(const Vector2& other) const { return Vector2(x + other.x, y + other.y); }
    Vector2 operator-(const Vector2& other) const { return Vector2(x - other.x, y - other.y); }
    Vector2 operator*(double scalar) const { return Vector2(x * scalar, y * scalar); }
    double magnitude() const { return sqrt(x * x + y * y); }
    Vector2 normalized() const {
        double mag = magnitude();
        return mag > 0 ? Vector2(x / mag, y / mag) : Vector2(0, 0);
    }
};

void fillCircle(SDL_Renderer* renderer, double centerX, double centerY, double radius) {
    for (double x = centerX - radius; x <= centerX + radius; x++) {
        for (double y = centerY - radius; y <= centerY + radius; y++) {
            double dx = x - centerX;
            double dy = y - centerY;
            if (dx * dx + dy * dy <= radius * radius) {
                SDL_RenderDrawPoint(renderer, (int)x, (int)y);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Black Hole Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Vector2 blackHolePos(WIDTH / 2.0, HEIGHT / 2.0);
    Vector2 earthPos(100, HEIGHT / 2.0); 
    Vector2 earthVel(5, 0); 

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        Vector2 r = blackHolePos - earthPos;
        double distance = r.magnitude();
        if (distance > 0) {
            Vector2 forceDir = r.normalized();
            double forceMag = G * BLACK_HOLE_MASS * EARTH_MASS / (distance * distance);
            Vector2 force = forceDir * forceMag;

            Vector2 accel = force * (1.0 / EARTH_MASS);

            earthVel = earthVel + accel * DT;
            earthPos = earthPos + earthVel * DT;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        fillCircle(renderer, blackHolePos.x, blackHolePos.y, BLACK_HOLE_RADIUS);

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        fillCircle(renderer, earthPos.x, earthPos.y, EARTH_RADIUS);

        SDL_RenderPresent(renderer);

        SDL_Delay(16); 
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
