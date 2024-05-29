#include <stdlib.h>

#include <raylib.h>
#include <raymath.h>
#include "ModUpdateCamera.h"

#include "playState.h"

#include "menuElements.h"

#include "renderer.h"
#include "player.h"
#include "npc.h"

#define INC_Y (10)
#define INC_X (10)
#define FONT_SIZE (25)

void explore(enum playState *playState, struct playInfo *info) {
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
        .font = &info->fonts[0],
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
        .font = &info->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };
    struct button map = {
        .text = "Mapa",
        .isActive = 0,
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
        .isActive = 1,
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
        .font = &info->fonts[0],
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
        .font = &info->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color2,
        .spaceing = 0
    };

    struct Object2D **render = createRenderer(info);

    Texture2D floor = LoadTexture("resources\\textures\\floor\\1.png");

    int shopInteraction = 0;

    CalculateButtonPosition(&save);
    CalculateButtonPosition(&equipment);
    CalculateButtonPosition(&map);
    CalculateButtonPosition(&pause);
    CalculateButtonPosition(&missions);
    CalculateButtonPosition(&shop);

    int i = 0;

    if (info->shouldDestroy == 1) {
        unloadCharacter(&info->chosen);
        info->shouldDestroy = 0;
    }

    info->resumeState = EXPLORE;
    while (!WindowShouldClose() && *playState == EXPLORE) {
        i += 1;

        if ((i / 10) % 4 == 0) {
            info->player.character.direction = 0;
            assemblePlayerTexture(info, &info->player.character);
        }
        else if ((i / 10) % 4 == 1) {
            info->player.character.direction = 1;
            assemblePlayerTexture(info, &info->player.character);
        }
        else if ((i / 10) % 4 == 2) {
            info->player.character.direction = 2;
            assemblePlayerTexture(info, &info->player.character);
        }
        else if ((i / 10) % 4 == 3) {
            info->player.character.direction = 3;
            assemblePlayerTexture(info, &info->player.character);
        }

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
                DrawFloors(info);

                RenderTextures(render, info->enemyQuantity + info->sellersQuantity + 1, info->camera);
            EndMode3D();

            DrawButton(save);
            DrawButton(equipment);
            DrawButton(map);
            DrawButton(pause);
            DrawButton(missions);
            if (shopInteraction) DrawButton(shop);
        EndTextureMode();

        BeginDrawing();
            DrawTextureRec(info->screenCamera->texture, *info->screenRect, (Vector2) { 0, 0 }, WHITE);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseOver(save)) *playState = SAVE;
            else if (isMouseOver(map)) *playState = MAP;
            else if (isMouseOver(equipment)) *playState = EQUIPEMENT;
            else if (isMouseOver(pause)) *playState = PAUSE;
            else if (isMouseOver(missions)) *playState = MISSIONS;
            else if (shopInteraction) if (isMouseOver(shop)) {
                *playState = DIALOG;
                findShop(info);
            }

        }
        else if (IsKeyPressed(KEY_P)) {
            EnableCursor();
            *playState = PAUSE;
        }

        detectFight(info, playState);
        hitbox(info);
        followPlayer(info);
        hitboxShop(info, &shopInteraction);
    }

    UnloadTexture(floor);
    free(render);
}