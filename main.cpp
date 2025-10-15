/**
 * Author: Perry Huang
 * Assignment: Lunar Lander
 * Date due: 2025-10-25, 11:59pm
 * I pledge that I have completed this assignment without
 * collaborating with anyone else, in conformance with the
 * NYU School of Engineering Policies and Procedures on
 * Academic Misconduct.
 */

#include "raylib.h"

// Enums
enum AppStatus { TERMINATED, RUNNING };
enum Direction { NONE, UP, DOWN, LEFT, RIGHT };

// Global Constants
constexpr int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 450, FPS = 60, SIDES = 4;

constexpr Vector2 ORIGIN = {SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0};

// Global Variables
AppStatus gAppStatus = RUNNING;

float gPreviousTicks = 0.0f;

// Function Declarations
void initialise();
void processInput();
void update();
void render();
void shutdown();
bool isColliding(const Vector2* positionA, const Vector2* scaleA, const Vector2* positionB, const Vector2* scaleB);

// Function Definitions
void initialise() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello raylib!");

    SetTargetFPS(FPS);
}

void processInput() {
    if (WindowShouldClose()) gAppStatus = TERMINATED;
}

void update() {
    // if the game is over, return early because there are no more calculations
    float ticks = (float)GetTime();
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks = ticks;
}

void render() {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    EndDrawing();
}

void shutdown() {
    CloseWindow();  // Close window and OpenGL context
}

int main() {
    initialise();

    while (gAppStatus == RUNNING) {
        processInput();
        update();
        render();
    }

    shutdown();

    return 0;
}
