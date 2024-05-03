#include <stdio.h>

#include <raylib.h>

#include "state.h"

#include "menuElement.h"

#define INC_Y (10)
#define INC_X (10)
#define FONT_SIZE (25)

void newGame(enum state *state, Font fonts[]) {
    const int height = GetScreenHeight() >> 1;
    const int spaceY = INC_Y + INC_Y + FONT_SIZE + 10;
    const int spaceX = 90;

    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };

    struct menuElement title = {
        .text = "Nowa gra",
        .x = GetScreenWidth() >> 1,
        .y = 100,
        .incX = 0,
        .incY = 0,
        .font = &fonts[0],
        .fontSize = 100,
        .fontColor = BLACK,
        .color = BLANK,
        .hoverColor = BLANK,
        .spaceing = 0
    };
    struct menuElement startGame = {
        .text = "Rozpocznij grę",
        .x = ( GetScreenWidth() >> 1 ) - spaceX,
        .y = height + 4 * spaceY,
        .incX = INC_X,
        .incY = INC_Y,
        .font = &fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };
    struct menuElement goBack = {
        .text = "Powrót",
        .x = ( GetScreenWidth() >> 1 ) + spaceX,
        .y = height + 4 * spaceY,
        .incX = INC_X,
        .incY = INC_Y,
        .font = &fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };

    while (!WindowShouldClose() && *state == NEW_GAME) {
        BeginDrawing();
            ClearBackground(color);

            DrawMenuElement(title);
            DrawMenuElement(startGame);
            DrawMenuElement(goBack);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseOver(startGame)) *state = EXPLORE;
            else if (isMouseOver(goBack)) *state = MENU;
        }
    }
}