#include <raylib.h>
#include "state.h"
#include "button.h"
#include "inputBox.h"

#define INC_Y (10)
#define INC_X (10)
#define FONT_SIZE (25)

void newGame(enum state *state, struct menuInfo *info) {
    const int height = GetScreenHeight() >> 1;
    const int spaceY = INC_Y + INC_Y + FONT_SIZE + 10;
    const int spaceX = 90;

    Color backgroundColor = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color buttonBackgroundColor = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color buttonBackgroundHoverColor = { .r = 78, .g = 215, .b = 50, .a = 105 };
    Color activeBorderColor = { .r = 0, .g = 0, .b = 0, .a = 255 };
    Color borderColor = { .r = 78, .g = 78, .b = 78, .a = 255 };
    Color inputColor = { .r = 78, .g = 78, .b = 78, .a = 255 };

    struct button title = {
        .text = "Nowa gra",
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
    struct button startGame = {
        .text = "Rozpocznij grę",
        .x = ( GetScreenWidth() >> 1 ) - spaceX,
        .y = height + 4 * spaceY,
        .incX = INC_X,
        .incY = INC_Y,
        .font = &info->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = buttonBackgroundColor,
        .hoverColor = buttonBackgroundHoverColor,
        .spaceing = 0
    };
    struct button goBack = {
        .text = "Powrót",
        .x = ( GetScreenWidth() >> 1 ) + spaceX,
        .y = height + 4 * spaceY,
        .incX = INC_X,
        .incY = INC_Y,
        .font = &info->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = buttonBackgroundColor,
        .hoverColor = buttonBackgroundHoverColor,
        .spaceing = 0
    };
    struct button gameSaveName = {
        .text = "Nazwa zapisu",
        .x = 80,
        .y = 300,
        .incX = INC_X,
        .incY = INC_Y,
        .font = &info->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = BLANK,
        .hoverColor = BLANK,
        .spaceing = 0
    };
    struct inputBox inputGameSaveName = {
        .text = "      \0",
        .currentLength = 0,
        .isActive = false,
        .x = 170,
        .y = 300,
        .incX = INC_X,
        .incY = INC_Y,
        .font = &info->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = inputColor,
        .borderActiveColor = activeBorderColor,
        .borderColor = borderColor,
        .spaceing = 0
    };
    struct button characterName = {
        .text = "Nazwa postaci",
        .x = 80,
        .y = 400,
        .incX = INC_X,
        .incY = INC_Y,
        .font = &info->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = BLANK,
        .hoverColor = BLANK,
        .spaceing = 0
    };
    struct inputBox inputCharacterName = {
        .text = "      \0",
        .currentLength = 0,
        .isActive = false,
        .x = 170,
        .y = 400,
        .incX = INC_X,
        .incY = INC_Y,
        .font = &info->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = inputColor,
        .borderActiveColor = activeBorderColor,
        .borderColor = borderColor,
        .spaceing = 0
    };

    while (!WindowShouldClose() && *state == NEW_GAME) {
        BeginDrawing();
            ClearBackground(backgroundColor);

            DrawButton(gameSaveName);
            DrawInputBox(&inputGameSaveName);
            DrawButton(characterName);
            DrawInputBox(&inputCharacterName);
            DrawButton(title);
            DrawButton(startGame);
            DrawButton(goBack);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseOver(startGame)) *state = PLAY;
            else if (isMouseOver(goBack)) *state = MENU;
        }
    }
}