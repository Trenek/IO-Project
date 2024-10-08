#include <raylib.h>

#include "state.h"

#include "menuElements.h"
#include "removeDirectory.h"
#include "saveData.h"

#define INC_Y (10)
#define INC_X (10)
#define FONT_SIZE (25)

#define RELOAD_SAVES break

void loadGame(enum state *state, struct menuInfo *info) {
    const int height = GetScreenHeight() >> 1;
    const int spaceY = INC_Y + INC_Y + FONT_SIZE + 10;
    const int spaceX = 90;

    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };

    struct button title = {
        .text = "Wczytywanie gry",
        .isActive = 1,
        .init = {
            .x = GetScreenWidth() >> 1,
            .y = 50,
            .incX = 0,
            .incY = 0,
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
    struct button loadGame = {
        .text = "Wczytaj",
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
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };
    struct button remove = {
        .text = "Usuń",
        .isActive = 1,
        .init = {
            .x = (GetScreenWidth() >> 1),
            .y = height + 4 * spaceY,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1
        },
        .font = &info->resources.fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
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
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };
    struct choiceBox saves = {
        .rowQuantity = 5,
        .wideness = 5,
        .loadActive = &loadGame.isActive,
        .init =  {
            .x = GetScreenWidth() >> 1,
            .y = GetScreenHeight() >> 1,
            .width = GetScreenWidth() >> 1,
            .incX = 15,
            .incY = 15,
            .posX = 1,
            .posY = 1
        },
        .font = &info->resources.fonts[0],
        .fontColor = BLACK,
        .fontSize = 40,
        .spaceing = 0,
        .color = GREEN,
        .activeBorderColor = RED,
        .inactiveBorderColor = BLACK,
        .hoverColor = PINK
    };

    CalculateButtonPosition(&title);
    CalculateButtonPosition(&loadGame);
    CalculateButtonPosition(&remove);
    CalculateButtonPosition(&goBack);

    initializeChoiceBox(&saves);

    while (!WindowShouldClose() && *state == LOAD_GAME) {
        BeginDrawing();
            ClearBackground(color);

            DrawButton(title);
            DrawButton(loadGame);
            DrawButton(remove);
            DrawButton(goBack);

            DrawChoiceBox(&saves);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseOver(loadGame)) *state = PLAY;
            else if (isMouseOver(goBack)) *state = MENU;
            else if (isMouseOver(remove)) {
                removeDirectory(TextFormat("saves\\%s", saves.saveData[saves.chosenRow + saves.rowQuantity * saves.page].text));
                RELOAD_SAVES;
            }

            UpdateChoiceBox(&saves, info);

            remove.isActive = loadGame.isActive;
        }
    }

    freeChoiceBox(&saves);
}
