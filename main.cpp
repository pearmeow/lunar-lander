/**
 * Author: Perry Huang
 * Assignment: Lunar Lander
 * Date due: 2025-10-25, 11:59pm
 * I pledge that I have completed this assignment without
 * collaborating with anyone else, in conformance with the
 * NYU School of Engineering Policies and Procedures on
 * Academic Misconduct.
 */

#include <raylib.h>

#include <charconv>
#include <cstring>

#include "CS3113/Rocket.h"

// Global Constants
constexpr int SCREEN_WIDTH = 1600, SCREEN_HEIGHT = 900, FPS = 60, SIDES = 4;

constexpr Vector2 ORIGIN = {SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0};

constexpr char ROCKET_FP[] = "assets/rocket.png";
constexpr char BLOCK_FP[] = "assets/block.png";

// Global Variables
AppStatus gAppStatus = RUNNING;
Rocket* gRocket = nullptr;
Vector2 gRocketScale = {50.0f, 50.0f};
float gPreviousTicks = 0.0f;
Vector2 gBlockScale = {100.0f, 100.0f};
Entity* gBlocks = nullptr;

// allocate enough space to put win/lose messages in later
bool gIsGameOver = false;
char gGameOverMessage[10] = "";
char gFuel[20] = "Fuel: ";

// Function Declarations
void initialise();
void processInput();
void update();
void render();
void shutdown();
bool isColliding(const Vector2* positionA, const Vector2* scaleA, const Vector2* positionB, const Vector2* scaleB);

// Function Definitions
void initialise() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Lunar Lander");
    gRocket = new Rocket(ORIGIN, gRocketScale, ROCKET_FP);
    gBlocks = new Entity[5];
    for (size_t i = 0; i < 5; ++i) {
        gBlocks[i].setTexture(BLOCK_FP);
        gBlocks[i].setPosition({ORIGIN.x + i * gBlockScale.x, SCREEN_HEIGHT - gBlockScale.y});
        gBlocks[i].setScale(gBlockScale);
        gBlocks[i].setColliderDimensions(gBlockScale);
    }
    gRocket->displayCollider();
    SetTargetFPS(FPS);
}

void processInput() {
    if (WindowShouldClose()) gAppStatus = TERMINATED;

    // skip processing if game is over
    if (gIsGameOver) {
        return;
    }

    if (IsKeyDown(KEY_SPACE)) {
        gRocket->setFlying(true);
    } else {
        gRocket->setFlying(false);
    }
    if (IsKeyDown(KEY_A)) {
        gRocket->moveLeft();
    }
    if (IsKeyDown(KEY_D)) {
        gRocket->moveRight();
    }
}

void update() {
    float ticks = (float)GetTime();
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks = ticks;

    // skip updating if game is over
    if (gIsGameOver) {
        return;
    }

    // replace nullptr with terrain later
    gRocket->update(deltaTime, gBlocks, 5);
    // if the rocket reaches a lose condition
    if (gRocket->isCrashed(SCREEN_WIDTH, SCREEN_HEIGHT)) {
        // some safe string copying
        gIsGameOver = true;
        strncpy(gGameOverMessage, "You lose!", 9);
    } else if (gRocket->isLanded()) {
        // if the rocket reaches a win condition
        // some more safe string copying
        gIsGameOver = true;
        strncpy(gGameOverMessage, "You win!", 8);
    }
    // convert float to char*
    if (gRocket->getFuel() > 0.0f) {
        std::to_chars(gFuel + 6, gFuel + 20, gRocket->getFuel());
    } else {
        // probably inefficient
        strncpy(gFuel, "Fuel: 0.0", 20);
    }
}

void render() {
    BeginDrawing();
    gRocket->render();
    for (size_t i = 0; i < 5; ++i) {
        gBlocks[i].render();
    }
    DrawText(gGameOverMessage, ORIGIN.x, 0.0f, 60, WHITE);
    DrawText(gFuel, 10.0f, 10.0f, 30, WHITE);
    ClearBackground(BLACK);
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
