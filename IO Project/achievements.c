#include <raylib.h>

#include "state.h"
#include "menuInfo.h"

#include "button.h"

#define INC_Y (10)
#define INC_X (10)
#define FONT_SIZE (25)

void achievements(enum state *state, struct menuInfo *info) {
    const int height = GetScreenHeight() >> 1;
    const int spaceY = INC_Y + INC_Y + FONT_SIZE + 10;

    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };

    struct button menuTitle = {
        .text = "Osiągnięcia",
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
    struct button goBack = {
        .text = "Powrót",
        .x = GetScreenWidth() >> 1,
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

    while (!WindowShouldClose() && *state == ACHIEVEMENTS) {
        BeginDrawing();
            ClearBackground(color);

            DrawButton(menuTitle);
            DrawButton(goBack);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseOver(goBack)) *state = MENU;
        }
    }
}