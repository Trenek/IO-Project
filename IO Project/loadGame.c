#include <raylib.h>

#include "state.h"

#include "menuElements.h"

#define INC_Y (10)
#define INC_X (10)
#define FONT_SIZE (25)

void loadGame(enum state *state, struct menuInfo *info) {
    const int height = GetScreenHeight() >> 1;
    const int spaceY = INC_Y + INC_Y + FONT_SIZE + 10;
    const int spaceX = 90;

    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };

    struct button title = {
        .text = "Wczytywanie gry",
        .init = {
            .x = GetScreenWidth() >> 1,
            .y = 100,
            .incX = 0,
            .incY = 0,
            .posX = 1,
            .posY = 1
        },
        .font = &info->fonts[0],
        .fontSize = 100,
        .fontColor = BLACK,
        .color = BLANK,
        .hoverColor = BLANK,
        .spaceing = 0
    };
    struct button loadGame = {
        .text = "Wczytaj",
        .init = {
            .x = (GetScreenWidth() >> 1) - spaceX,
            .y = height + 4 * spaceY,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1
        },
        .font = &info->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };
    struct button goBack = {
        .text = "Powrót",
        .init = {
            .x = (GetScreenWidth() >> 1) + spaceX,
            .y = height + 4 * spaceY,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1
        },
        .font = &info->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };
    struct choiceBox loadSave = {
        .text = "",
        .init = {
            .x = GetScreenWidth() >> 1,
            .y = 100,
            .incX = 0,
            .incY = 0,
            .posX = 1,
            .posY = 1
        },
        .font = &info->fonts[0],
        .fontSize = 45,
        .fontColor = BLUE,
        .color = GREEN,
        .borderColor = RED,
        .spaceing = 0,
  };


    CalculateButtonPosition(&title);
    CalculateButtonPosition(&loadGame);
    CalculateButtonPosition(&goBack);
    CalculateChoiceBoxPosition(&loadSave);


    while (!WindowShouldClose() && *state == LOAD_GAME) {
        BeginDrawing();
            ClearBackground(color);
            DrawChoiceBox(loadSave);
            DrawButton(title);
            DrawButton(loadGame);
            DrawButton(goBack);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseOver(loadGame)) *state = PLAY;
            else if (isMouseOver(goBack)) *state = MENU;
        }
    }
}