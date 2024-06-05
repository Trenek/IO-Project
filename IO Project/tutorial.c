#include <raylib.h>

#include "state.h"

#include "menuElements.h"


#define INC_Y (10)
#define INC_X (10)
#define FONT_SIZE (25)

void tutorial(enum state* state, struct menuInfo* info) {


    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };

    struct button goBack = {
        .text = "Powrót",
        .isActive = 1,
        .init = {
            .x = 50,
            .y = 50,
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

    struct tutorialSlide slide = {
    .init = {
        .x = GetScreenWidth() >> 1,
        .y = GetScreenHeight() >> 1,
        .width = GetScreenWidth() >> 1,
        .incX = 15,
        .incY = 15,
        .posX = 1,
        .posY = 1
    },
    .font = &info->resources.fonts[0],
    .fontSize = FONT_SIZE,
    .fontColor = BLACK,
    .backgroundColor = RED,
    .titleDescriptionColor = BLUE,
    .borderColor = RED,
    .spaceing = 0,
    .color = GREEN,
    };


    char tipPath[15];
    sprintf(tipPath, "samouczek/tip%i", 1);
 
    FilePathList imgsList = LoadDirectoryFiles(tipPath);

    Image tutorialImage = LoadImage(imgsList.paths[1]);
    Texture2D imageAsTexture = LoadTextureFromImage(tutorialImage);
    char* description = LoadFileText(imgsList.paths[0]);   
    char* title = LoadFileText(imgsList.paths[2]);
    printf("%s %s", description, title);
    CalculateButtonPosition(&goBack);

    initializeTutorialSlideBox(&slide, tutorialImage);


    while (!WindowShouldClose() && *state == TUTORIAL) {
        BeginDrawing();
            ClearBackground(color);

            DrawButton(goBack);

            DrawTutorialSlideBox(&slide, imageAsTexture, title, description);

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseOver(goBack)) *state = MENU;

            UnloadFileText(title);                            
            UnloadFileText(description);                            
            UnloadTexture(imageAsTexture);
            UnloadImage(tutorialImage);
            UnloadDirectoryFiles(imgsList);

            sprintf(tipPath, "samouczek/tip%i", UpdateTutorialSlideBox(&slide));
            imgsList = LoadDirectoryFiles(tipPath);

            tutorialImage = LoadImage(imgsList.paths[1]);
            description = LoadFileText(imgsList.paths[0]);
            title = LoadFileText(imgsList.paths[2]);
            imageAsTexture = LoadTextureFromImage(tutorialImage);
        }
    }

}