#include <raylib.h>

#include <string.h>
#include <stdio.h>

#include "state.h"

#include "menuElements.h"

#define INC_Y (10)
#define INC_X (10)
#define FONT_SIZE (25)

static void saveToFile(struct slideBox *framesPerSecondSlide, struct slideBox *windowResolution, struct slideBox *textureQuality, int fullScreen) {
    FILE *file = fopen("config.cfg", "w");
    int x, y;

    sscanf(framesPerSecondSlide->options[framesPerSecondSlide->currentOption], "%i", &x);
    fprintf(file, "%i\n", x);
    fprintf(file, "%i\n", textureQuality->currentOption);
    sscanf(windowResolution->options[windowResolution->currentOption], "%ix%i", &x, &y);
    fprintf(file, "%i %i\n", x, y);
    fprintf(file, "%i\n", fullScreen);

    fclose(file);
}

static void loadActualSettings(struct menuInfo *info, struct slideBox *framesPerSecondSlide, struct slideBox *windowResolution, struct slideBox *textureQuality, struct slideBox *fullScreenState) {
    windowResolution->currentOption = 0;
    while (windowResolution->currentOption < windowResolution->numberOfOptions && strcmp(windowResolution->options[windowResolution->numberOfOptions], windowResolution->options[windowResolution->currentOption]) != 0) {
        windowResolution->currentOption += 1;
    }

    framesPerSecondSlide->currentOption = 0;
    while (framesPerSecondSlide->currentOption < framesPerSecondSlide->numberOfOptions && strcmp(framesPerSecondSlide->options[framesPerSecondSlide->numberOfOptions], framesPerSecondSlide->options[framesPerSecondSlide->currentOption]) != 0) {
        framesPerSecondSlide->currentOption += 1;
    }

    textureQuality->currentOption = info->textureQuality;
    fullScreenState->currentOption = info->fullScreenMode;
}

void settings(enum state *state, struct menuInfo *info) {
    const int height = (GetScreenHeight() >> 1);
    const int spaceY = INC_Y + INC_Y + FONT_SIZE + 10;

    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };

    struct button title = {
        .text = "Ustawienia",
        .isActive = 1,
        .init = {
            .x = GetScreenWidth() >> 1,
            .y = 100,
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

    struct button framesPerSecond = {
        .text = "Klatki na sekundę",
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
        .color = color2,
        .hoverColor = color2,
        .spaceing = 0
    };
    struct button windowDimensions = {
        .text = "Wymiary okna",
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
        .color = color2,
        .hoverColor = color2,
        .spaceing = 0
    };
    struct button textureResolution = {
        .text = "Rozdzielczość tekstur",
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
        .color = color2,
        .hoverColor = color2,
        .spaceing = 0
    };
    struct button fullScreenButton = {
        .text = "Tryb Pełnoekranowy",
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
        .color = color2,
        .hoverColor = color2,
        .spaceing = 0
    };
    struct button resetSettings = {
        .text = "Zresetuj ustawienia",
        .isActive = 1,
        .init = {
            .x = (GetScreenWidth() >> 1),
            .y = height + 3 * spaceY,
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

    struct button accept = {
        .text = "Accept",
        .isActive = 1,
        .init = {
            .x = (GetScreenWidth() >> 1) - (GetScreenWidth() >> 3),
            .y = height + 4 * spaceY,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 2,
            .posY = 1
        },
        .font = &info->resources.fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };
    struct button restart = {
        .text = "Restart",
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
            .x = (GetScreenWidth() >> 1) + (GetScreenWidth() >> 3),
            .y = height + 4 * spaceY,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 0,
            .posY = 1
        },
        .font = &info->resources.fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };

    struct slideBox framesPerSecondSlide = {
        .numberOfOptions = 6,
        .isActive = false,
        .currentOption = 0,
        .options = (const char *[]){
            "15",
            "30",
            "60",
            "90",
            "120",
            "240",
            TextFormat("%i", info->framesPerSecond)
        },
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
        .color = color2,
        .borderActiveColor = RED,
        .borderColor = BLACK,
        .spaceing = 0
    };
    struct slideBox windowResolution = {
        .numberOfOptions = 23,
        .isActive = false,
        .currentOption = 0,
        .options = (const char *[]){
            "640x360",
            "640x480",
            "800x600",
            "1024x768",
            "1280x720",
            "1280x800",
            "1280x1024",
            "1360x768",
            "1366x768",
            "1440x900",
            "1536x864",
            "1600x900",
            "1600x1200",
            "1680x1050",
            "1920x1080",
            "1920x1200",
            "2048x1152",
            "2048x1536",
            "2560x1080",
            "2560x1440",
            "2560x1600",
            "3440x1440",
            "3840x2160",
            TextFormat("%ix%i", info->windowWidth, info->windowHeight)
        },
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
        .color = color2,
        .borderActiveColor = RED,
        .borderColor = BLACK,
        .spaceing = 0
    };
    struct slideBox textureQuality = {
        .numberOfOptions = 3,
        .isActive = false,
        .currentOption = 1,
        .options = (const char *[]){
            "Low",
            "Medium",
            "High"
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
        .color = color2,
        .borderActiveColor = RED,
        .borderColor = BLACK,
        .spaceing = 0
    };
    struct slideBox fullScreenState = {
        .numberOfOptions = 2,
        .isActive = false,
        .currentOption = 0,
        .options = (const char *[]){
            "Wyłączony",
            "Włączony"
        },
        .init = {
            .x = (GetScreenWidth() >> 1) + (GetScreenWidth() >> 3),
            .y = height + 2 * spaceY,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1,
            .width = 300
        },
        .font = &info->resources.fonts[1],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .borderActiveColor = RED,
        .borderColor = BLACK,
        .spaceing = 0
    };

    loadActualSettings(info, &framesPerSecondSlide, &windowResolution, &textureQuality, &fullScreenState);
    
    CalculateButtonPosition(&title);

    CalculateButtonPosition(&framesPerSecond);
    CalculateButtonPosition(&textureResolution);
    CalculateButtonPosition(&windowDimensions);
    CalculateButtonPosition(&fullScreenButton);
    CalculateButtonPosition(&resetSettings);

    CalculateButtonPosition(&accept);
    CalculateButtonPosition(&restart);
    CalculateButtonPosition(&goBack);

    CalculateSlideBoxPosition(&framesPerSecondSlide);
    CalculateSlideBoxPosition(&textureQuality);
    CalculateSlideBoxPosition(&windowResolution);
    CalculateSlideBoxPosition(&fullScreenState);

    while (!WindowShouldClose() && *state == SETTINGS) {
        BeginDrawing();
            ClearBackground(color);

            DrawButton(title);

            DrawButton(framesPerSecond);
            DrawButton(textureResolution);
            DrawButton(windowDimensions);
            DrawButton(fullScreenButton);
            DrawButton(resetSettings);

            DrawButton(accept);
            DrawButton(restart);
            DrawButton(goBack);

            DrawSlideBox(&framesPerSecondSlide);
            DrawSlideBox(&textureQuality);
            DrawSlideBox(&windowResolution);
            DrawSlideBox(&fullScreenState);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseOver(goBack)) *state = MENU;
            else if (isMouseOver(restart)) *state = RELOAD;
            else if (isMouseOver(resetSettings)) {
                loadActualSettings(info, &framesPerSecondSlide, &windowResolution, &textureQuality, &fullScreenState);
            }
            else if (isMouseOver(accept)) {
                saveToFile(&framesPerSecondSlide, &windowResolution, &textureQuality, fullScreenState.currentOption);
            }
        }

        UpdateSlideBox(&framesPerSecondSlide);
        UpdateSlideBox(&textureQuality);
        UpdateSlideBox(&windowResolution);
        UpdateSlideBox(&fullScreenState);
    }
}
