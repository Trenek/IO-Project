#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

#include "renderer.h"
#include "player.h"

//#define FULL_SCREEN

void UnloadTextures(Texture2D texture[][4]) {
    int i = 0;
    int j = 0;

    while (i < 4) {
        j = 0;
        while (j < 4) {
            UnloadTexture(texture[i][j]);
            j += 1;
        }
        i += 1;
    }
}

int example2(void) {

#ifdef FULL_SCREEN
    InitWindow(GetScreenWidth(), GetScreenHeight(), "Prototype");
    ToggleFullscreen();
#else
    InitWindow(800, 450, "Prototype");
#endif

    rlEnableDepthTest();
    SetTargetFPS(240);

    Camera cam = {
        .position.x = 0,
        .position.z = -10,
        .position.y = 0,
        .up.y = 1,
        .fovy = 45,
    };

    Texture2D ludz = LoadTexture("resources/textures/ludzik2.png");
    Texture2D mag = LoadTexture("resources/textures/mag.png");
    Texture2D arys = LoadTexture("resources/textures/arystokrata2.png");

    Texture2D pixel[4][4] = {
        { LoadTexture("resources/textures/pixel/WarriorBack0.png"), LoadTexture("resources/textures/pixel/WarriorBack1.png"), LoadTexture("resources/textures/pixel/WarriorBack0.png"), LoadTexture("resources/textures/pixel/WarriorBack2.png") },
        { LoadTexture("resources/textures/pixel/WarriorRight0.png"), LoadTexture("resources/textures/pixel/WarriorRight1.png"), LoadTexture("resources/textures/pixel/WarriorRight0.png"), LoadTexture("resources/textures/pixel/WarriorRight2.png") },
        { LoadTexture("resources/textures/pixel/WarriorFront0.png"), LoadTexture("resources/textures/pixel/WarriorFront1.png"), LoadTexture("resources/textures/pixel/WarriorFront0.png"), LoadTexture("resources/textures/pixel/WarriorFront2.png") },
        { LoadTexture("resources/textures/pixel/WarriorLeft0.png"), LoadTexture("resources/textures/pixel/WarriorLeft1.png"), LoadTexture("resources/textures/pixel/WarriorLeft0.png"), LoadTexture("resources/textures/pixel/WarriorLeft2.png") }
    };

    Matrix mat = { 0 };
    struct Object2D objects[4] = {
        { .position = (Vector3){ 4, 1, 0 }, .sizeV = { pixel[2][0].width / (0.5f * pixel[2][0].height), pixel[2][0].height / (0.5f * pixel[2][0].height) }, .texture = &pixel[2][0], .Animation = &pixel, .animFrame = 0, .state = 0 },
        { .position = (Vector3){ -4, 1, 0 }, .sizeV = { arys.width / (0.5f * arys.height), arys.height / (0.5f * arys.height) }, .texture = &arys, .Animation = NULL, .animFrame = 0, .state = 0 },
        { .position = (Vector3){ 0, 1, 4 }, .sizeV = { mag.width / (0.5f * mag.height), mag.height / (0.5f * mag.height) }, .texture = &mag, .Animation = NULL, .animFrame = 0, .state = 0 },
        { .position = (Vector3){ 0, 1, -4 }, .sizeV = { 2, 2 }, .texture = &ludz, .Animation = NULL, .animFrame = 0, .state = 0 }
    };
    struct player player = {
        .object = objects,
        .speedY = 0
    };
    struct ObjectsToRender render[] = {
        { objects + 0, 4 },
        { objects + 1, 4 },
        { objects + 2, 4 },
        { objects + 3, 4 }
    };
    int i = 1;

    InitAudioDevice();              // Initialize audio device
    Music music1 = LoadMusicStream("resources/music/music1.mp3");
    Music music2 = LoadMusicStream("resources/music/music1.mp3");

    PlayMusicStream(music1);
    PlayMusicStream(music2);

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_B)) UpdateMusicStream(music1);
        else UpdateMusicStream(music2);

        // Toggle camera controls
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            if (IsCursorHidden())
                EnableCursor();
            else
                DisableCursor();
        }

        if (IsCursorHidden()) {
            movePlayer(&player, &cam);

            cam.target = player.object->position;
            UpdateCamera(&cam, CAMERA_THIRD_PERSON);
        }
        else {
            player.object->state = 0;
            gravity(&player);

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

        BeginDrawing();
            ClearBackground(WHITE);

            BeginMode3D(cam);
                DrawGrid(100, 1);
        
                DrawPlane((Vector3) { 0, 0, 0 }, (Vector2) { 100, 100 }, VIOLET);
                DrawCube((Vector3) { 0, 0.5f, 0 }, 1, 1, 1, GRAY);

                DrawCube((Vector3) { 1, 0.125f, 0 }, 0.25f, 0.25f, 0.25f, RED);
                DrawCube((Vector3) { 0, 0.125f, 1 }, 0.25f, 0.25f, 0.25f, BLUE);

                RenderTextures(render, 4, cam);
            EndMode3D();
            DrawText(TextFormat("(x, y, z) = (%3.0f, %3.0f, %3.0f)", cam.position.x, cam.position.y, cam.position.z), 0, 0, 20, VIOLET);
        EndDrawing();
    }

    UnloadTexture(ludz);
    UnloadTexture(mag);
    UnloadTexture(arys);
    UnloadTextures(pixel);

    UnloadMusicStream(music1);
    UnloadMusicStream(music2);

    CloseAudioDevice();         // Close audio device (music streaming is automatically stopped)

    CloseWindow();

    return 0;
}