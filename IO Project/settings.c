#include <raylib.h>

#include "state.h"

#include "menuElements.h"

#define INC_Y (10)
#define INC_X (10)
#define FONT_SIZE (25)

void settings(enum state *state, struct menuInfo *info) {
    const int height = GetScreenHeight() >> 1;
    const int spaceY = INC_Y + INC_Y + FONT_SIZE + 10;
    const int spaceX = 90;

    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };

    struct button title = {
        .text = "Ustawienia",
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
    struct button textureResolution = {
        .text = "Rozdzielczość tekstur",
        .init = {
            .x = 150,
            .y = height,
            .incX = 0,
            .incY = 0,
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
    struct button windowDimensions = {
        .text = "Wymiary okna",
        .init = {
            .x = 150,
            .y = height + spaceY,
            .incX = 0,
            .incY = 0,
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
    struct button fullScreen = {
        .text = "Tryb Pełnoekranowy",
        .init = {
            .x = 150,
            .y = height + 2 * spaceY,
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
    struct button resetSettings = { //ewentualnie domyślne ustawienia
        .text = "Zresetuj ustawienia",
        .init = {
            .x = 150,
            .y = height + 3 * spaceY,
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
    struct button restart = {  //tutaj nie do końca wiem na czym stanęlśmy z restar/reload/akceptuj/zapisz
        .text = "Restart",
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

    struct slideBox setWindowDimensions = {
        .numberOfOptions = 3,
        .isActive = false,
        .currentOption = 0,
        .options = {
            "1000x1000",
            "2000x2000",
            "3000x3000"
        },
        .init = {
            .x = (GetScreenWidth() >> 1),
            .y = height,
            .incX = 0,
            .incY = 0,
            .posX = 1,
            .posY = 1,
            .width = 150
        },
        .font = &info->fonts[1],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .borderActiveColor = RED,
        .borderColor = BLACK,
        .spaceing = 0
    };
    struct slideBox setTextureResolution = {
        .numberOfOptions = 3,
        .isActive = false,
        .currentOption = 1,
        .options = {
            "Low",
            "Medium",
            "High"
        },
        .init = {
            .x = (GetScreenWidth() >> 1),
            .y = height + spaceY,
            .incX = 0,
            .incY = 0,
            .posX = 1,
            .posY = 1,
            .width = 150
        },
        .font = &info->fonts[1],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .borderActiveColor = RED,
        .borderColor = BLACK,
        .spaceing = 0
    };

    CalculateButtonPosition(&title);
    CalculateButtonPosition(&textureResolution);
    CalculateButtonPosition(&windowDimensions);
    CalculateButtonPosition(&fullScreen);
    CalculateButtonPosition(&resetSettings);
    CalculateButtonPosition(&restart);
    CalculateButtonPosition(&goBack);

    CalculateSlideBoxPosition(&setWindowDimensions);
    CalculateSlideBoxPosition(&setTextureResolution);

    while (!WindowShouldClose() && *state == SETTINGS) {
        BeginDrawing();
            ClearBackground(color);

            DrawButton(title);
            DrawButton(textureResolution);
            DrawButton(windowDimensions);
            DrawSlideBox(&setWindowDimensions);
            DrawSlideBox(&setTextureResolution);
            DrawButton(fullScreen);
            DrawButton(resetSettings);
            DrawButton(restart);
            DrawButton(goBack);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseOver(goBack)) *state = MENU;
            else if (isMouseOver(restart)) *state = RELOAD;
        }

        UpdateSelectionBox(&setWindowDimensions);
        UpdateSelectionBox(&setTextureResolution);
    }
}
