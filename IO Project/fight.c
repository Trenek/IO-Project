#include <raylib.h>
#include <raymath.h>

#include "playState.h"

#include "menuElements.h"

#include "renderer.h"
#include "player.h"

#define INC_Y (10)
#define INC_X (10)
#define FONT_SIZE (25)

void fight(enum playState *playState, struct playInfo *info) {
    const int height = GetScreenHeight() >> 4;
    const int spaceY = INC_Y + INC_Y + FONT_SIZE + 10;

    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };

    struct button back = {
        .text = "Wróć",
        .init = {
            .x = GetScreenWidth() >> 4,
            .y = height + 0 * spaceY,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 0,
            .posY = 1
        },
        .font = &info->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };

    struct character player = info->player.character;
    struct character enemy = info->enemy;

    player.direction = FRONT;
    assemblePlayerTexture(info, &player);

    struct Object2D *render[] = {
        &player.object,
        &enemy.object
    };

    Camera3D fightCamera = {
        .position = {
            .x = 10,
            .y = 3,
            .z = 0
        },
        .up.y = 1,
        .fovy = 45
    };

    player.object.position = (Vector3){ .x = 1, .y = 0, .z = 4 };
    enemy.object.position = (Vector3){ .x = 1, .y = 0, .z = -4 };

    CalculateButtonPosition(&back);
    
    info->resumeState = FIGHT;
    while (!WindowShouldClose() && *playState == FIGHT) {
        UpdateMusicStream(info->music[0]);

        BeginTextureMode(*info->screenCamera);
            ClearBackground(color);

            BeginMode3D(fightCamera);
                DrawGrid(100, 1);

                RenderTextures(render, sizeof(render) / sizeof(struct Object2D *), fightCamera);
            EndMode3D();

            DrawButton(back);
        EndTextureMode();

        BeginDrawing();
            DrawTextureRec(info->screenCamera->texture, *info->screenRect, (Vector2) { 0, 0 }, WHITE);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseOver(back)) *playState = EXPLORE;
        }
        else if (IsKeyPressed(KEY_P)) {
            *playState = PAUSE;
        }
    }
}