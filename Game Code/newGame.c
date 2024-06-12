#include <raylib.h>

#include "state.h"

#include "menuElements.h"

#include "savefile.h"

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
    Color borderColor = { .r = 78, .g = 78, .b = 78, .a = 255 };
    Color inputColor = { .r = 78, .g = 78, .b = 78, .a = 255 };

    struct button title = {
        .text = "Nowa gra",
        .isActive = 1,
        .init = {
            .x = GetScreenWidth() >> 1,
            .y = 100,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1
        },
        .font = &info->resources.fonts[0],
        .fontSize = 100,
        .fontColor = BLACK,
        .color = BLANK,
        .hoverColor = BLANK,
        .spaceing = 0
    };

    struct button gameSaveName = {
        .text = "Nazwa zapisu",
        .isActive = 1,
        .init = {
            .x = (GetScreenWidth() >> 3),
            .y = height - spaceY,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 0,
            .posY = 1
        },
        .font = &info->resources.fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = BLANK,
        .hoverColor = BLANK,
        .spaceing = 0
    };
    struct button characterName = {
        .text = "Nazwa postaci",
        .isActive = 1,
        .init = {
            .x = (GetScreenWidth() >> 3),
            .y = height,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 0,
            .posY = 1
        },
        .font = &info->resources.fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = BLANK,
        .hoverColor = BLANK,
        .spaceing = 0
    };
    struct button difficultyLevel = {
        .text = "Poziom trudności",
        .isActive = 1,
        .init = {
            .x = (GetScreenWidth() >> 3),
            .y = height + spaceY,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 0,
            .posY = 1
        },
        .font = &info->resources.fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = BLANK,
        .hoverColor = BLANK,
        .spaceing = 0
    };

    struct button createCharacter = {
        .text = "Kreator postaci",
        .isActive = 1,
        .init = {
            .x = (GetScreenWidth() >> 3),
            .y = height + 2 * spaceY,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 0,
            .posY = 1
        },
        .font = &info->resources.fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = buttonBackgroundColor,
        .hoverColor = buttonBackgroundHoverColor,
        .spaceing = 0
    };
    struct button startGame = {
        .text = "Rozpocznij grę",
        .isActive = 0,
        .init = {
            .x = (GetScreenWidth() >> 1) - spaceX,
            .y = height + 4 * spaceY,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1
        },
        .font = &info->resources.fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = buttonBackgroundColor,
        .hoverColor = buttonBackgroundHoverColor,
        .spaceing = 0
    };
    struct button goBack = {
        .text = "Powrót",
        .isActive = 1,
        .init = {
            .x = (GetScreenWidth() >> 1) + spaceX,
            .y = height + 4 * spaceY,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1
        },
        .font = &info->resources.fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = buttonBackgroundColor,
        .hoverColor = buttonBackgroundHoverColor,
        .spaceing = 0
    };

    struct button errorButton = {
        .text = "Zapis o takiej nazwie już istnieje!",
        .isActive = 1,
        .init = {
            .x = GetScreenWidth() >> 1,
            .y = height + (int)(2.5 * spaceY),
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1
        },
        .font = &info->resources.fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = RED,
        .hoverColor = RED,
        .spaceing = 0
    };

    struct inputBox inputGameSaveName = {
        .text = "Wpisz Nazwę Zapisu",
        .currentLength = 0,
        .isActive = false,
        .init = {
            .x = (GetScreenWidth() >> 1) + (GetScreenWidth() >> 3),
            .y = height - spaceY,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1,
            .width = 300
        },
        .font = &info->resources.fonts[1],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = inputColor,
        .borderActiveColor = BLACK,
        .borderColor = borderColor,
        .spaceing = 0
    };
    struct inputBox inputCharacterName = {
        .text = "Wpisz Nazwę Postaci",
        .currentLength = 0,
        .isActive = false,
        .init = {
            .x = (GetScreenWidth() >> 1) + (GetScreenWidth() >> 3),
            .y = height,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1,
            .width = 300
        },
        .font = &info->resources.fonts[1],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = inputColor,
        .borderActiveColor = BLACK,
        .borderColor = borderColor,
        .spaceing = 0
    };

    struct slideBox setDifficultyLevel = {
        .numberOfOptions = 3,
        .isActive = false,
        .currentOption = 0,
        .options = (const char *[]){
            "Easy",
            "Medium",
            "Hard"
        },
        .init = {
            .x = (GetScreenWidth() >> 1) + (GetScreenWidth() >> 3),
            .y = height + spaceY,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1,
            .width = 300
        },
        .font = &info->resources.fonts[1],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = inputColor,
        .borderActiveColor = RED,
        .borderColor = BLACK,
        .spaceing = 0
    };

    int error = 0;

    CalculateButtonPosition(&title);
    CalculateButtonPosition(&createCharacter);
    CalculateButtonPosition(&startGame);
    CalculateButtonPosition(&goBack);
    CalculateButtonPosition(&gameSaveName);
    CalculateButtonPosition(&characterName);
    CalculateButtonPosition(&difficultyLevel);
    CalculateButtonPosition(&errorButton);

    CalculateInputBoxPosition(&inputGameSaveName);
    CalculateInputBoxPosition(&inputCharacterName);
    CalculateSlideBoxPosition(&setDifficultyLevel);

    while (!WindowShouldClose() && *state == NEW_GAME) {
        BeginDrawing();
        ClearBackground(backgroundColor);

            DrawButton(gameSaveName);
            DrawButton(characterName);
            DrawButton(difficultyLevel);
            DrawButton(title);
            DrawButton(createCharacter);
            DrawButton(startGame);
            DrawButton(goBack);
            if (error) DrawButton(errorButton);

            DrawInputBox(&inputGameSaveName);
            DrawInputBox(&inputCharacterName);
            DrawSlideBox(&setDifficultyLevel);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseOver(startGame)) {
                while (inputGameSaveName.text[inputGameSaveName.currentLength - 1] == ' ') {
                    inputGameSaveName.text[inputGameSaveName.currentLength - 1] = 0;
                    inputGameSaveName.currentLength -= 1;
                }

                error = CreateNewSave(inputGameSaveName.text, inputCharacterName.text, info->body, setDifficultyLevel.currentOption);
                if (error == 0) {
                    *state = PLAY;
                    strcpy(info->saveName, inputGameSaveName.text);
                }
            }
            else if (isMouseOver(createCharacter)) *state = CHARACTER_CREATOR;
            else if (isMouseOver(goBack)) *state = MENU;
        }

        UpdateInputBox(&inputGameSaveName);
        UpdateInputBox(&inputCharacterName);
        UpdateSlideBox(&setDifficultyLevel);

        startGame.isActive = (inputGameSaveName.currentLength < 1 || inputCharacterName.currentLength < 1) ? 0 : 1;
    }
}