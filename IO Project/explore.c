#include <raylib.h>

#include "state.h"
#include "menuInfo.h"

#include "button.h"

#define INC_Y (10)
#define INC_X (10)
#define FONT_SIZE (25)

void explore(enum playState *playState, struct menuInfo *info) {
    const int height = GetScreenHeight() >> 1;
    const int spaceY = INC_Y + INC_Y + FONT_SIZE + 10;
    

    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };


    struct button title = {
        .text = "Eksploracja",
        .x = GetScreenWidth() >> 1,
        .y = 100,
        .incX = 0,
        .incY = 0,
        .font = &info->fonts[0],
        .fontSize = 100,
        .fontColor = BLACK,
        .color = BLANK,
        .hoverColor = BLANK,
        .spaceing = 0
    };
    struct button save = {
        .text = "Zapisz",
        .x = (GetScreenWidth() >> 1),
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
    struct button equipment = {
        .text = "Ekwipunek",
        .x = (GetScreenWidth() >> 1),
        .y = height + 3 * spaceY,
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
        .x = (GetScreenWidth() >> 1),
        .y = height + 4 * spaceY,
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
        .x = (GetScreenWidth() >> 1),
        .y = height + 5 * spaceY,
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
        BeginDrawing();
            ClearBackground(color);

            DrawButton(title);
            DrawButton(save);
            DrawButton(equipment);
            DrawButton(map);
            DrawButton(pause);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseOver(save)) *playState = SAVE;
            else if (isMouseOver(map)) *playState = MAP;
            else if (isMouseOver(equipment)) *playState = EQUIPEMENT;
            else if (isMouseOver(pause)) *playState = PAUSE;
        }
    }
}