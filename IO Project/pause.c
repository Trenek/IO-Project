#include <stdio.h>

#include <raylib.h>

#include "playState.h"

#include "button.h"

#define INC_Y (10)
#define INC_X (10)
#define FONT_SIZE (25)

void pause(enum playState *state, struct playInfo *info) {
    const int height = (GetScreenHeight() >> 1) + 80;
    const int space = FONT_SIZE + INC_Y * 2 + 10;

    Color color1 = { .r = 100, .g = 100, .b = 100, .a = 200 };
    Color color2 = { .r = 0, .g = 0, .b = 0, .a = 60 };

    struct button title = {
        .text = "Pauza",
        .x = GetScreenWidth() >> 1,
        .y = GetScreenHeight() >> 2,
        .incX = 10,
        .incY = 10,
        .font = &info->fonts[0],
        .fontSize = 100,
        .fontColor = BLACK,
        .color = BLANK,
        .hoverColor = BLANK,
        .spaceing = 0
    };
    struct button resume = {
        .text = "Wznów",
        .x = GetScreenWidth() >> 1,
        .y = height,
        .incX = INC_X,
        .incY = INC_Y,
        .font = &info->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = BLANK,
        .hoverColor = color2,
        .spaceing = 0
    };
    struct button menu = {
        .text = "Wyjdź do Menu",
        .x = GetScreenWidth() >> 1,
        .y = height + space,
        .incX = INC_X,
        .incY = INC_Y,
        .font = &info->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = BLANK,
        .hoverColor = color2,
        .spaceing = 0
    };
    struct button exit = {
        .text = "Wyjdź do Pulpitu",
        .x = GetScreenWidth() >> 1,
        .y = height + 2 * space,
        .incX = INC_X,
        .incY = INC_Y,
        .font = &info->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = BLANK,
        .hoverColor = color2,
        .spaceing = 0
    };

    *state = PAUSE;
    do {
        BeginDrawing();
            ClearBackground(color1);
            if (info->screenCamera != NULL) DrawTextureRec(info->screenCamera->texture, *info->screenRect, (Vector2) { 0, 0 }, WHITE);
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight() + 100, color1);

            DrawButton(title);
            DrawButton(resume);
            DrawButton(menu);
            DrawButton(exit);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseOver(resume)) *state = EXPLORE;
            else if (isMouseOver(menu)) *state = RETURN;
            else if (isMouseOver(exit)) *state = DESKTOP;
        }
        if (IsKeyPressed(KEY_P)) {
            *state = EXPLORE;
        }
    } while (*state == PAUSE && !WindowShouldClose());
}