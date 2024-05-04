#include <raylib.h>

#include "state.h"

#include "button.h"

#define INC_Y (10)
#define INC_X (10)
#define FONT_SIZE (25)

void menu(enum state *state, Font fonts[]) {
    const int height = GetScreenHeight() >> 1;
    const int space = INC_Y + INC_Y + FONT_SIZE + 10;

    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };

    struct button menuTitle = {
        .text = "Menu Startowe",
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
    struct button newGame = {
        .text = "Nowa Gra",
        .x = GetScreenWidth() >> 1,
        .y = height,
        .incX = INC_X,
        .incY = INC_Y,
        .font = &fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };
    struct button loadGame = {
        .text = "Wczytaj Grę",
        .x = GetScreenWidth() >> 1,
        .y = height + space,
        .incX = INC_X,
        .incY = INC_Y,
        .font = &fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };
    struct button settings = {
        .text = "Ustawienia",
        .x = GetScreenWidth() >> 1,
        .y = height + 2 * space,
        .incX = INC_X,
        .incY = INC_Y,
        .font = &fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };
    struct button achivements = {
        .text = "Osiągnięcia",
        .x = GetScreenWidth() >> 1,
        .y = height + 3 * space,
        .incX = INC_X,
        .incY = INC_Y,
        .font = &fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };
    struct button exit = {
        .text = "Wyjdź do Pulpitu",
        .x = GetScreenWidth() >> 1,
        .y = height + 4 * space,
        .incX = INC_X,
        .incY = INC_Y,
        .font = &fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };

    while (!WindowShouldClose() && *state == MENU) {
        BeginDrawing();
            ClearBackground(color);

            DrawButton(menuTitle);
            DrawButton(newGame);
            DrawButton(loadGame);
            DrawButton(settings);
            DrawButton(achivements);
            DrawButton(exit);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseOver(newGame)) *state = NEW_GAME;
            else if (isMouseOver(loadGame)) *state = LOAD_GAME;
            else if (isMouseOver(settings)) *state = SETTINGS;
            else if (isMouseOver(achivements)) *state = ACHIVEMENTS;
            else if (isMouseOver(exit)) *state = EXIT;
        }
    }
}