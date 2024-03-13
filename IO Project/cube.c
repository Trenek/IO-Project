/*******************************************************************************************
*
*   raylib [core] example - Picking in 3d mode
*
*   Example originally created with raylib 1.3, last time updated with raylib 4.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

int example(void) {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "raylib [core] example - 3d picking");
    ToggleFullscreen();
    // Define the camera to look into our 3d world
    Camera camera = {
        .position = (Vector3){ 10.0f, 10.0f, 10.0f }, // Camera position
        .target = (Vector3){ 0.0f, 0.0f, 0.0f },      // Camera looking at point
        .up = (Vector3){ 0.0f, 1.0f, 0.0f },          // Camera up vector (rotation towards target)
        .fovy = 45.0f,                                // Camera field-of-view Y
        .projection = CAMERA_PERSPECTIVE,             // Camera projection type
    };
    Vector3 cubePosition = { 0.0f, 1.0f, 0.0f };
    Vector3 cubeSize = { 2.0f, 2.0f, 2.0f };

    Ray ray = { 0 };                    // Picking line ray
    RayCollision collision = { 0 };     // Ray collision hit info

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (IsCursorHidden()) 
            UpdateCamera(&camera, CAMERA_THIRD_PERSON);

        // Toggle camera controls
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            if (IsCursorHidden()) 
                EnableCursor();
            else 
                DisableCursor();
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (!collision.hit) {
                ray = GetMouseRay(GetMousePosition(), camera);

                // Check collision between ray and box
                collision = GetRayCollisionBox(ray,
                    (BoundingBox) {
                    (Vector3) {
                    cubePosition.x - cubeSize.x / 2, cubePosition.y - cubeSize.y / 2, cubePosition.z - cubeSize.z / 2
                },
                        (Vector3) {
                        cubePosition.x + cubeSize.x / 2, cubePosition.y + cubeSize.y / 2, cubePosition.z + cubeSize.z / 2
                    }
                });
            }
            else 
                collision.hit = false;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                if (collision.hit) {
                    DrawCube(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, RED);
                    DrawCubeWires(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, MAROON);

                    DrawCubeWires(cubePosition, cubeSize.x + 0.2f, cubeSize.y + 0.2f, cubeSize.z + 0.2f, GREEN);
                }
                else {
                    DrawCube(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, GRAY);
                    DrawCubeWires(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, DARKGRAY);
                }

                DrawRay(ray, MAROON);
                DrawGrid(10, 1.0f);
            EndMode3D();

            DrawText("Try clicking on the box with your mouse!", 240, 10, 20, DARKGRAY);

            if (collision.hit) DrawText("BOX SELECTED", (screenWidth - MeasureText("BOX SELECTED", 30)) / 2, (int)(screenHeight * 0.1f), 30, GREEN);

            DrawText("Right click mouse to toggle camera controls", 10, 430, 10, GRAY);

            DrawFPS(10, 10);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

/**********************************************************************************************
*
*   raylib-extras, examples-c * examples for Raylib in C
*
*   full 3d billboards * an example of doing billboards that rotate to face the camera in any orientation
*
*   LICENSE: ZLib
*
*   Copyright (c) 2022 Jeffery Myers
*
*   Permission is hereby granted, free of charge, to any person obtaining a copy
*   of this software and associated documentation files (the "Software"), to deal
*   in the Software without restriction, including without limitation the rights
*   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*   copies of the Software, and to permit persons to whom the Software is
*   furnished to do so, subject to the following conditions:
*
*   The above copyright notice and this permission notice shall be included in all
*   copies or substantial portions of the Software.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*   SOFTWARE.
*
**********************************************************************************************/

#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <stddef.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "renderer.h"

struct player {
    struct Object2D* object;
    float speedY;
};

void move(struct player* player) {
    float deltaTime = GetFrameTime();

    if (player->object->position.y >= 1) {
        if (!(player->object->position.y == 1 && player->speedY == 0)) {
            player->object->position.y += ((player->speedY) + ((-9.81f) * deltaTime / 2.0f)) * deltaTime;
            if (player->object->position.y < 1) {
                player->object->position.y = 1;
            }
            player->speedY = player->speedY + (-9.81f * deltaTime);
        }
    }
    else {
        player->object->position.y = 1;
        player->speedY = 0;
    }
}

int example2(void) {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - Full 3D billboards");
    rlEnableDepthTest();
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // setup a camera
    Camera cam = {
        .position.x = 0,
        .position.z = -10,
        .position.y = 0,
        .up.y = 1,
        .fovy = 45,
    };

    Texture2D box = LoadTexture("resources/panel_woodPaperDetailSquare.png");
    Matrix mat = { 0 };
    struct Object2D objects[4] = {
        { .position = (Vector3){ 4, 1, 0 }, .size = 2, .texture = &box },
        { .position = (Vector3){ -4, 1, 0 }, .size = 2, .texture = &box },
        { .position = (Vector3){ 0, 1, 4 }, .size = 2, .texture = &box },
        { .position = (Vector3){ 0, 1, -4 }, .size = 2, .texture = &box },
    };
    struct player player = {
        .object = objects,
        .speedY = 0
    };
    struct ObjectsToRender render = {
        .objects = objects,
        .size = 4,

    };
    int i = 1;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Toggle camera controls
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            if (IsCursorHidden())
                EnableCursor();
            else
                DisableCursor();
        }

        Vector2 ve = {
            .x = player.object->position.x - cam.position.x,
            .y = player.object->position.z - cam.position.z,
        };

        ve = Vector2Normalize(ve);
        ve.x /= 10;
        ve.y /= 10;
        Vector3 vec = {
            .x = ve.x,
            .y = 0,
            .z = ve.y
        };

        if (IsKeyDown(KEY_I)) {
            player.object->position.x += ve.x;
            player.object->position.z += ve.y;
            cam.position.x += ve.x;
            cam.position.z += ve.y;
        }
        if (IsKeyDown(KEY_K)) {
            ve = Vector2Rotate(ve, M_PI);
            player.object->position.x += ve.x;
            player.object->position.z += ve.y;
            cam.position.x += ve.x;
            cam.position.z += ve.y;
        }
        if (IsKeyDown(KEY_L)) {
            ve = Vector2Rotate(ve, M_PI / 2);
            player.object->position.x += ve.x;
            player.object->position.z += ve.y;
            cam.position.x += ve.x;
            cam.position.z += ve.y;
        }
        if (IsKeyDown(KEY_J)) {
            ve = Vector2Rotate(ve, 3 * M_PI / 2);
            player.object->position.x += ve.x;
            player.object->position.z += ve.y;
            cam.position.x += ve.x;
            cam.position.z += ve.y;
        }
        if (IsKeyPressed(KEY_SPACE)) player.speedY = 4;

        if (IsCursorHidden()) {
            cam.target = player.object->position;
            UpdateCamera(&cam, CAMERA_THIRD_PERSON);
        }
        else {
            cam.target = (Vector3){ 0, 0, 0 };
            // rotate the camera around the center
            mat = MatrixRotate((Vector3) { 0, 1, 0 }, DEG2RAD* GetFrameTime() * 45);
            cam.position = Vector3Transform(cam.position, mat);
            cam.position.y += i * DEG2RAD * GetFrameTime() * 450;

            if (cam.position.y > 10) {
                i = -1;
            }
            else if (cam.position.y < 0.5) {
                i = 1;
            }
            // move the camera up and down so that it has a X axis rotation too
            //cam.position.y = sinf(GetTime()) * 5;
        }

        if (cam.position.y > 10) {
            cam.position.y = 10.f;
        }
        else if (cam.position.y < 0.5) {
            cam.position.y = 0.5f;
        }
        move(&player);

        BeginDrawing();
            ClearBackground(WHITE);

            BeginMode3D(cam);
                DrawGrid(100, 1);
        
                // draw a reference cube      
                DrawPlane((Vector3) { 0, 0, 0 }, (Vector2) { 100, 100 }, VIOLET);
                DrawCube((Vector3) { 0, 0.5f, 0 }, 1, 1, 1, GRAY);

                DrawCube((Vector3) { 1, 0.125f, 0 }, 0.25f, 0.25f, 0.25f, RED);
                DrawCube((Vector3) { 0, 0.125f, 1 }, 0.25f, 0.25f, 0.25f, BLUE);

                // draw 4 billboards
                RenderTextures(&render, cam);
            EndMode3D();
            //DrawText(TextFormat("(x, y, z) = (%4.1f, %4.1f, %4.1f)", cam.position.x, cam.position.y, cam.position.z), 0, 0, 20, VIOLET);
            DrawText(TextFormat("(x, y, z) = (%3.0f, %3.0f, %3.0f)", cam.position.x, cam.position.y, cam.position.z), 0, 0, 20, VIOLET);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}