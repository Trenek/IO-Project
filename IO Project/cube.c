#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <stddef.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "renderer.h"
#include "player.h"

#define SUPPORT_FILEFORMAT_SVG 1

/*******************************************************************************************
*
*   raylib [textures] example - gif playing
*
*   Example originally created with raylib 4.2, last time updated with raylib 4.2
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2021-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#define MAX_FRAME_DELAY     20
#define MIN_FRAME_DELAY      1

int example2(void) {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

   // InitWindow(screenWidth, screenHeight, "raylib [shaders] example - Full 3D billboards");
    InitWindow(GetScreenWidth(), GetScreenHeight(), "lol");
    ToggleFullscreen();

    rlEnableDepthTest();
    SetTargetFPS(240);

    Camera cam = {
        .position.x = 0,
        .position.z = -10,
        .position.y = 0,
        .up.y = 1,
        .fovy = 45,
    };

    Texture2D ludz = LoadTexture("resources/ludzik2.png");
    Texture2D mag = LoadTexture("resources/mag.png");
    Texture2D arys = LoadTexture("resources/arystokrata2.png");

    Texture2D pixel[4][4] = {
        { LoadTexture("resources/pixel/WarriorBack0.png"), LoadTexture("resources/pixel/WarriorBack1.png"), LoadTexture("resources/pixel/WarriorBack0.png"), LoadTexture("resources/pixel/WarriorBack2.png") },
        { LoadTexture("resources/pixel/WarriorRight0.png"), LoadTexture("resources/pixel/WarriorRight1.png"), LoadTexture("resources/pixel/WarriorRight0.png"), LoadTexture("resources/pixel/WarriorRight2.png") },
        { LoadTexture("resources/pixel/WarriorFront0.png"), LoadTexture("resources/pixel/WarriorFront1.png"), LoadTexture("resources/pixel/WarriorFront0.png"), LoadTexture("resources/pixel/WarriorFront2.png") },
        { LoadTexture("resources/pixel/WarriorLeft0.png"), LoadTexture("resources/pixel/WarriorLeft1.png"), LoadTexture("resources/pixel/WarriorLeft0.png"), LoadTexture("resources/pixel/WarriorLeft2.png") }
    };

    Matrix mat = { 0 };
    struct Object2D objects[4] = {
        { .position = (Vector3){ 4, 1, 0 }, .sizeV = { pixel[2][0].width / (0.5f * pixel[2][0].height), pixel[2][0].height / (0.5f * pixel[2][0].height) }, .texture = &pixel[2][0], .Animation = &pixel, .animFrame = 0, .state = 0 },
        { .position = (Vector3){ -4, 1, 0 }, .sizeV = { arys.width / (0.5f * arys.height), arys.height / (0.5f * arys.height) }, .texture = &arys, .Animation = NULL, .animFrame = NULL, .state = 0 },
        { .position = (Vector3){ 0, 1, 4 }, .sizeV = { mag.width / (0.5f * mag.height), mag.height / (0.5f * mag.height) }, .texture = &mag, .Animation = NULL, .animFrame = NULL, .state = 0 },
        { .position = (Vector3){ 0, 1, -4 }, .sizeV = { 2, 2 }, .texture = &ludz, .Animation = NULL, .animFrame = NULL, .state = 0 }
    };
    struct player player = {
        .object = objects,
        .speedY = 0,
    };
    struct ObjectsToRender render[] = {
        { objects + 0, 4 },
        { objects + 1, 4 },
        { objects + 2, 4 },
        { objects + 3, 4 }
    };
    int i = 1;

    while (!WindowShouldClose()) {
        // Toggle camera controls
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            if (IsCursorHidden())
                EnableCursor();
            else
                DisableCursor();
        }

        //movePlayer(&player, &cam);

        if (IsCursorHidden()) {
            movePlayer(&player, &cam);

            cam.target = player.object->position;
            UpdateCamera(&cam, CAMERA_THIRD_PERSON);
        }
        else {
            player.object->state = 0;
            gravity(&player, &cam);

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
        }

        if (cam.position.y > 10) {
            cam.position.y = 10.f;
        }
        else if (cam.position.y < 0.5) {
            cam.position.y = 0.5f;
        }
       // move(&player);

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
                RenderTextures(render, 4, cam);
            EndMode3D();
            //DrawText(TextFormat("(x, y, z) = (%4.1f, %4.1f, %4.1f)", cam.position.x, cam.position.y, cam.position.z), 0, 0, 20, VIOLET);
            DrawText(TextFormat("(x, y, z) = (%3.0f, %3.0f, %3.0f)", cam.position.x, cam.position.y, cam.position.z), 0, 0, 20, VIOLET);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}