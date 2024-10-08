#include <stdlib.h>

#include <raylib.h>
#include <raymath.h>

#include "playState.h"

#include "menuElements.h"

#include "renderer.h"
#include "player.h"
#include "hitbox.h"

#define INC_Y (10)
#define INC_X (10)
#define FONT_SIZE (25)

void explore(enum playState *state, struct playInfo *info) {
    const int height = GetScreenHeight() >> 4;
    const int spaceY = INC_Y + INC_Y + FONT_SIZE + 10;

    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };

    struct button save = {
        .text = "Zapisz",
        .isActive = 1,
        .init = {
            .x = GetScreenWidth() >> 4,
            .y = height + 0 * spaceY,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 0,
            .posY = 1
        },
        .font = &info->resources->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };
    struct button equipment = {
        .text = "Ekwipunek",
        .isActive = 1,
        .init = {
            .x = GetScreenWidth() >> 4,
            .y = height + 1 * spaceY,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 0,
            .posY = 1
        },
        .font = &info->resources->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };
    struct button pause = {
        .text = "Pauza",
        .isActive = 1,
        .init = {
            .x = GetScreenWidth() - (GetScreenWidth() >> 4),
            .y = height,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 2,
            .posY = 1
        },
        .font = &info->resources->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };
    struct button missions = {
        .text = "Misje",
        .isActive = 0,
        .init = {
            .x = GetScreenWidth() - (GetScreenWidth() >> 4),
            .y = height + spaceY,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 2,
            .posY = 1
        },
        .font = &info->resources->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };
    struct button shop = {
        .text = "Kliknij aby przejść do sklepu",
        .isActive = 1,
        .init = {
            .x = GetScreenWidth() >> 1,
            .y = GetScreenHeight() - (GetScreenHeight() >> 3),
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1
        },
        .font = &info->resources->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color2,
        .spaceing = 0
    };

    struct Object2D **render = createRenderer(info);

    int shopInteraction = 0;

    CalculateButtonPosition(&save);
    CalculateButtonPosition(&equipment);
    CalculateButtonPosition(&pause);
    CalculateButtonPosition(&missions);
    CalculateButtonPosition(&shop);

    int i = 0;

    if (info->shouldDestroy == 1) {
        UnloadCharacter(&info->chosen);
        info->shouldDestroy = 0;
    }

    info->resumeState = EXPLORE;
    while (!WindowShouldClose() && *state == EXPLORE) {
        i += 1;

        UpdateMusicStream(info->resources->music[0]);
        movePlayer(info, &info->save.player, &info->camera);

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            if (IsCursorHidden())
                EnableCursor();
            else
                DisableCursor();
        }

        updateCamera(info);

        BeginTextureMode(*info->screenCamera);
            ClearBackground(color);

            BeginMode3D(info->camera);
                DrawFloors(info);
                DrawCeilings(info);
                DrawWalls(info);

                RenderTextures(render, info->save.enemyQuantity + info->save.sellersQuantity + 1, info->camera);
            EndMode3D();

            DrawButton(save);
            DrawButton(equipment);
            DrawButton(pause);
            DrawButton(missions);
            if (shopInteraction) DrawButton(shop);
        EndTextureMode();

        BeginDrawing();
            DrawTextureRec(info->screenCamera->texture, *info->screenRect, (Vector2) { 0, 0 }, WHITE);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseOver(save)) *state = SAVE;
            else if (isMouseOver(equipment)) *state = EQUIPEMENT;
            else if (isMouseOver(pause)) *state = PAUSE;
            else if (isMouseOver(missions)) *state = MISSIONS;
            else if (shopInteraction) if (isMouseOver(shop)) {
                *state = DIALOG;
                findShop(info);
            }

        }
        else if (IsKeyPressed(KEY_P)) {
            EnableCursor();
            *state = PAUSE;
        }

        detectFight(info, state);
        hitbox(info);
        followPlayer(info);
        hitboxShop(info, &shopInteraction);
    }

    free(render);
}