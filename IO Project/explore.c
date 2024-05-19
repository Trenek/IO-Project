#include <stdlib.h>

#include <raylib.h>
#include <raymath.h>
#include "ModUpdateCamera.h"

#include "playState.h"

#include "menuElements.h"

#include "renderer.h"
#include "player.h"

#define INC_Y (10)
#define INC_X (10)
#define FONT_SIZE (25)


void hitbox(struct playInfo *info);
void explore(enum playState *playState, struct playInfo *info) {
    const int height = GetScreenHeight() >> 4;
    const int spaceY = INC_Y + INC_Y + FONT_SIZE + 10;

    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };

    struct button save = {
        .text = "Zapisz",
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
    struct button equipment = {
        .text = "Ekwipunek",
        .init = {
            .x = GetScreenWidth() >> 4,
            .y = height + 1 * spaceY,
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
    struct button map = {
        .text = "Mapa",
        .init = {
            .x = GetScreenWidth() >> 4,
            .y = height + 2 * spaceY,
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
    struct button pause = {
        .text = "Pauza",
        .init = {
            .x = GetScreenWidth() - (GetScreenWidth() >> 4),
            .y = height,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 2,
            .posY = 1
        },
        .font = &info->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };
    struct button fight = {
        .text = "Walcz",
        .init = {
            .x = GetScreenWidth() - (GetScreenWidth() >> 4),
            .y = height + 1 * spaceY,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 2,
            .posY = 1
        },
        .font = &info->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };

    struct Object2D **render = createRenderer(info);

    CalculateButtonPosition(&save);
    CalculateButtonPosition(&equipment);
    CalculateButtonPosition(&map);
    CalculateButtonPosition(&pause);
    CalculateButtonPosition(&fight);

    info->resumeState = EXPLORE;
    while (!WindowShouldClose() && *playState == EXPLORE) {
        UpdateMusicStream(info->music[0]);
        movePlayer(info, &info->player, &info->camera);

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            if (IsCursorHidden())
                EnableCursor();
            else
                DisableCursor();
        }
        if (IsCursorHidden()) {
            ModUpdateCamera(&info->camera, CAMERA_THIRD_PERSON);
        }
        info->camera.target = info->player.character.object.position;
        info->camera.target.y += info->player.character.object.sizeV.y / 2;

        BeginTextureMode(*info->screenCamera);
            ClearBackground(color);

            BeginMode3D(info->camera);
                DrawGrid(100, 1);

                RenderTextures(render, info->npcQuantity + 1, info->camera);
            EndMode3D();

            DrawButton(save);
            DrawButton(equipment);
            DrawButton(map);
            DrawButton(pause);
            DrawButton(fight);
        EndTextureMode();

        BeginDrawing();
            DrawTextureRec(info->screenCamera->texture, *info->screenRect, (Vector2) { 0, 0 }, WHITE);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseOver(save)) *playState = SAVE;
            else if (isMouseOver(map)) *playState = MAP;
            else if (isMouseOver(equipment)) *playState = EQUIPEMENT;
            else if (isMouseOver(pause)) *playState = PAUSE;
            else if (isMouseOver(fight)) {
                *playState = FIGHT;
                info->enemy = info->npc[0];
            }
        }
        else if (IsKeyPressed(KEY_P)) {
            EnableCursor();
            *playState = PAUSE;
        }

        hitbox(info);
    }

    free(render);
}