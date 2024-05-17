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
        .init = {
            .x = GetScreenWidth() >> 1,
            .y = 100,
            .incX = INC_X,
            .incY = INC_Y,
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
    struct button startGame = {
        .text = "Rozpocznij grę",
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
        .color = buttonBackgroundColor,
        .hoverColor = buttonBackgroundHoverColor,
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
        .color = buttonBackgroundColor,
        .hoverColor = buttonBackgroundHoverColor,
        .spaceing = 0
    };
    struct button gameSaveName = {
        .text = "Nazwa zapisu",
        .init = {
            .x = 80,
            .y = 300,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1
        },
        .font = &info->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = BLANK,
        .hoverColor = BLANK,
        .spaceing = 0
    };
    struct button characterName = {
        .text = "Nazwa postaci",
        .init = {
            .x = 80,
            .y = 400,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1
        },
        .font = &info->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = BLANK,
        .hoverColor = BLANK,
        .spaceing = 0
    };

    struct inputBox inputGameSaveName = {
        .text = "Wpisz Nazwę Zapisu",
        .currentLength = 0,
        .isActive = false,
        .init = {
            .x = 170,
            .y = 300,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 0,
            .posY = 1,
            .width = 400
        },
        .font = &info->fonts[1],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = inputColor,
        .borderActiveColor = activeBorderColor,
        .borderColor = borderColor,
        .spaceing = 0
    };
    struct inputBox inputCharacterName = {
        .text = "Wpisz Nazwę Postaci",
        .currentLength = 0,
        .isActive = false,
        .init = {
            .x = 170,
            .y = 400,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 0,
            .posY = 1,
            .width = 400
        },
        .font = &info->fonts[1],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = inputColor,
        .borderActiveColor = activeBorderColor,
        .borderColor = borderColor,
        .spaceing = 0
    };

    CalculateButtonPosition(&title);
    CalculateButtonPosition(&startGame);
    CalculateButtonPosition(&goBack);
    CalculateButtonPosition(&gameSaveName);
    CalculateButtonPosition(&characterName);

    CalculateInputBoxPosition(&inputGameSaveName);
    CalculateInputBoxPosition(&inputCharacterName);

    while (!WindowShouldClose() && *state == NEW_GAME) {
        BeginDrawing();
            ClearBackground(backgroundColor);

            DrawButton(gameSaveName);
            DrawButton(characterName);
            DrawButton(title);
            DrawButton(startGame);
            DrawButton(goBack);

            DrawInputBox(&inputGameSaveName);
            DrawInputBox(&inputCharacterName);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseOver(startGame)) *state = PLAY;
            else if (isMouseOver(goBack)) *state = MENU;
        }

        UpdateInputBox(&inputGameSaveName);
        UpdateInputBox(&inputCharacterName);
    }
}