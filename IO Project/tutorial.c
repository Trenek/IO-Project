#include <raylib.h>

#include "state.h"

#include "menuElements.h"

#include "tutorialSlide.h"

#define INC_Y (10)
#define INC_X (10)
#define FONT_SIZE (25)

void tutorial(enum state* state, struct menuInfo* info) {
    const int height = GetScreenHeight() >> 1;
    const int spaceY = INC_Y + INC_Y + FONT_SIZE + 10;

    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };

    struct button goBack = {
        .text = "Powrót",
        .init = {
            .x = 50,
            .y = 50,
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

    struct tutorialSlide slide = {
    .init = {
        .x = GetScreenWidth() >> 1,
        .y = height + 4 * spaceY,
        .incX = INC_X,
        .incY = INC_Y,
        .posX = 1,
        .posY = 1
    },
    .font = &info->fonts[0],
    .fontSize = FONT_SIZE,
    .fontColor = BLACK,
    .backgroundColor = color2,
    .titleDescriptionColor = BLUE,
    .borderColor = RED,
    .spaceing = 0
    };

    CalculateButtonPosition(&goBack);
    CalculateSlidePosition(&slide);

    FilePathList imgsList = LoadDirectoryFiles("../IO Project/dane/tutorialImgs");       // Load directory filepaths

    Image tutorialImage = LoadImage(imgsList.paths[0]);
    Texture2D imageAsTexture = LoadTextureFromImage(tutorialImage);

    while (!WindowShouldClose() && *state == TUTORIAL) {
        BeginDrawing();
        ClearBackground(color);

        DrawButton(goBack);
        DrawSlide(slide, "Title", "Description", imageAsTexture);

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseOver(goBack)) *state = MENU;
        }
    }
    UnloadTexture(imageAsTexture);
    UnloadImage(tutorialImage);
    UnloadDirectoryFiles(imgsList);
}