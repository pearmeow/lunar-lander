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

// for debugging
#include <charconv>
#include <cstring>

#include "CS3113/Block.h"
#include "CS3113/Rocket.h"

// Global Constants
constexpr int SCREEN_WIDTH = 1600, SCREEN_HEIGHT = 900, FPS = 60, SIDES = 4;
constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;
constexpr Vector2 ORIGIN = {SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0};

constexpr char ROCKET_FP[] = "./assets/rocket.png";
constexpr char TRAIL_FP[] = "./assets/fire.png";
constexpr char BLOCK_FP[] = "./assets/block.png";
constexpr char GREEN_BLOCK_FP[] = "./assets/greenBlock.png";
constexpr int NUM_BLOCKS = 6;

// Global Variables
AppStatus gAppStatus = RUNNING;
Rocket* gRocket = nullptr;
Entity* gTrail;
Vector2 gRocketScale = {50.0f, 50.0f};
Vector2 gTrailScale = {50.0f, 50.0f};
Vector2 gBlockScale = {100.0f, 100.0f};
Block* gBlocks = nullptr;

float gPreviousTicks = 0.0f;
float gTimeAccumulator = 0.0f;

// allocate enough space to put win/lose messages in later
bool gIsGameOver = false;
char gGameOverMessage[20] = "";
char gFuel[20] = "Fuel: ";

// Function Declarations
void initialise();
void processInput();
void update();
void render();
void shutdown();

// Function Definitions
void initialise() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Lunar Lander");
    gRocket = new Rocket(ORIGIN, gRocketScale, ROCKET_FP);
    gTrail = new Entity(ORIGIN, gTrailScale, TRAIL_FP, ATLAS, {1, 14},
                        {{RIGHT, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}}});
    gTrail->deactivate();
    gRocket->setTrail(gTrail);
    gBlocks = new Block[NUM_BLOCKS];
    for (size_t i = 0; i < NUM_BLOCKS - 1; ++i) {
        gBlocks[i].setTexture(BLOCK_FP);
        gBlocks[i].setPosition({ORIGIN.x + i * gBlockScale.x, SCREEN_HEIGHT - gBlockScale.y / 2.0f});
        gBlocks[i].setScale(gBlockScale);
        gBlocks[i].setColliderDimensions(gBlockScale);
    }
    gBlocks[0].moveUp();
    gBlocks[NUM_BLOCKS - 1].setTexture(GREEN_BLOCK_FP);
    gBlocks[NUM_BLOCKS - 1].setPosition({ORIGIN.x - 1 * gBlockScale.x, SCREEN_HEIGHT - gBlockScale.y / 2.0f});
    gBlocks[NUM_BLOCKS - 1].setScale(gBlockScale);
    gBlocks[NUM_BLOCKS - 1].setColliderDimensions(gBlockScale);
    gBlocks[NUM_BLOCKS - 1].setType(WIN);
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
        gRocket->turnLeft();
    }
    if (IsKeyDown(KEY_D)) {
        gRocket->turnRight();
    }
}

void update() {
    // skip updating if game is over
    if (gIsGameOver) {
        return;
    }

    float ticks = (float)GetTime();
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks = ticks;

    deltaTime += gTimeAccumulator;

    if (deltaTime < FIXED_TIMESTEP) {
        gTimeAccumulator = deltaTime;
        return;
    }

    while (deltaTime >= FIXED_TIMESTEP) {
        deltaTime -= FIXED_TIMESTEP;

        gRocket->update(FIXED_TIMESTEP, gBlocks, NUM_BLOCKS);
        gTrail->update(FIXED_TIMESTEP, nullptr, 0);
        // if the rocket reaches a lose condition
        // (crashes due to high velocity & wrong rotation or lands on a lose block or is out of bounds)
        if (gRocket->isCrashed() || gRocket->isOutOfBounds(SCREEN_WIDTH, SCREEN_HEIGHT)) {
            // some safe string copying
            gIsGameOver = true;
            strncpy(gGameOverMessage, "Mission Failed", 20);
        } else if (gRocket->isLanded()) {
            // if the rocket reaches a win condition
            // some more safe string copying
            gIsGameOver = true;
            strncpy(gGameOverMessage, "Mission Accomplished", 20);
        }

        for (size_t i = 0; i < NUM_BLOCKS; ++i) {
            gBlocks[i].update(FIXED_TIMESTEP, nullptr, 0);
            // printf("Block %lu pos: %f, %f\n", i, gBlocks[i].getPosition().x, gBlocks[i].getPosition().x);
            // printf("Block %lu scale: %f, %f\n", i, gBlocks[i].getScale().x, gBlocks[i].getScale().x);
            // printf("Block %lu collider: %f, %f\n", i, gBlocks[i].getColliderDimensions().x,
            //        gBlocks[i].getColliderDimensions().x);
        }
        // convert float to char*
        if (gRocket->getFuel() > 0.0f) {
            std::to_chars(gFuel + 6, gFuel + 20, gRocket->getFuel());
        } else {
            // PERF: probably inefficient
            strncpy(gFuel, "Fuel: 0.0", 20);
        }
    }
}

void render() {
    BeginDrawing();
    gRocket->render();
    for (size_t i = 0; i < NUM_BLOCKS; ++i) {
        gBlocks[i].render();
    }
    gTrail->render();
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
