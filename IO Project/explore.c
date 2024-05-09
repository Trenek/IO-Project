#include <raylib.h>

#include "playState.h"

#include "button.h"

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
        .x = GetScreenWidth() >> 4,
        .y = height + 0 * spaceY,
        .incX = INC_X,
        .incY = INC_Y,
        .font = &info->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };
    struct button equipment = {
        .text = "Ekwipunek",
        .x = GetScreenWidth() >> 4,
        .y = height + 1 * spaceY,
        .incX = INC_X,
        .incY = INC_Y,
        .font = &info->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };
    struct button map = {
        .text = "Mapa",
        .x = GetScreenWidth() >> 4,
        .y = height + 2 * spaceY,
        .incX = INC_X,
        .incY = INC_Y,
        .font = &info->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };
    struct button pause = {
        .text = "Pauza",
        .x = GetScreenWidth() - (GetScreenWidth() >> 4),
        .y = height,
        .incX = INC_X,
        .incY = INC_Y,
        .font = &info->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };

    while (!WindowShouldClose() && *playState == EXPLORE) {
        BeginTextureMode(*info->screenCamera);
            ClearBackground(color);

            DrawButtonLeft(save);
            DrawButtonLeft(equipment);
            DrawButtonLeft(map);
            DrawButtonRight(pause);
        EndTextureMode();
        BeginDrawing();
            DrawTextureRec(info->screenCamera->texture, *info->screenRect, (Vector2) { 0, 0 }, WHITE);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseOverLeft(save)) *playState = SAVE;
            else if (isMouseOverLeft(map)) *playState = MAP;
            else if (isMouseOverLeft(equipment)) *playState = EQUIPEMENT;
            else if (isMouseOverRight(pause)) *playState = PAUSE;
        }
    }
}