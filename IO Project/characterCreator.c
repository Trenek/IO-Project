#include <raylib.h>

#include "state.h"
#include "playState.h"
#include "load.h"
#include "character.h"

#include "menuElements.h"

#define INC_Y (5)
#define INC_X (10)
#define FONT_SIZE (25)

static void CalculateTexturesPosition(int bodyPosition[4][10][2], Vector2 texturePosition[10]) {
    for (int i = 0; i < 10; i++) {
        texturePosition[i] = (Vector2){
            .x = (float)bodyPosition[0][i][0] / 2 + 50,
            .y = (float)bodyPosition[0][i][1] / 2 + 150,
        };
    }
}

void characterCreator(enum state* state, struct menuInfo* info) {  
    const char *const bodyPartsNamesInPolish[10] = {
        [HEAD] = "Głowa",
        [LEFT_ARM] = "Lewe ramię",
        [RIGHT_ARM] = "Prawie ramię",
        [LEFT_FOOT] = "Lewa stopa",
        [RIGHT_FOOT] = "Prawa stopa",
        [LEFT_HAND] = "Lewa dłoń",
        [RIGHT_HAND] = "Prawa dłoń",
        [LEFT_LEG] = "Lewa noga",
        [RIGHT_LEG] = "Prawa dłoń",
        [TORSO] = "Tors"
    };

    Vector2 texturePosition[10];

    const int spaceY = INC_Y + INC_Y + FONT_SIZE;
    const int spaceX = 90;

    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };

    struct button title = {
        .text = "Kreator postaci",
        .isActive = 1,
        .init = {
            .x = GetScreenWidth() >> 1,
            .y = 10,
            .incX = 10,
            .incY = 10,
            .posX = 1,
            .posY = 0,
        },
        .font = &info->fonts[0],
        .fontSize = 100,
        .fontColor = BLACK,
        .color = BLANK,
        .hoverColor = BLANK,
        .spaceing = 0,
    };
    struct button confirm = {
        .text = "Zatwierdź",
        .isActive = 1,
        .init = {
            .x = (GetScreenWidth() >> 1) - spaceX,
            .y = (GetScreenHeight() >> 2) + 11 * spaceY,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1
        },
        .font = &info->fonts[0],
        .fontSize = 25,
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
            .y = (GetScreenHeight() >> 2) + 11 * spaceY,
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

    struct button labels[10];
    struct nSlideBox bodyPartSlideBoxes[10];
    
    if (info->isLoaded == 0) {
        loadBodyPosition(info);
        loadBodyParts(info);

        info->isLoaded = 1;
    }

    for (int i = 0; i < 10; i++) {
        labels[i] = (struct button){
            .text = bodyPartsNamesInPolish[i],
            .isActive = 1,
            .init = {
                .x = (GetScreenWidth() >> 1),
                .y = (GetScreenHeight() >> 2) + i * spaceY,
                .incX = INC_X,
                .incY = INC_Y,
                .posX = 0,
                .posY = 1
            },
            .font = &info->fonts[0],
            .fontSize = FONT_SIZE,
            .fontColor = BLACK,
            .color = BLANK,
            .hoverColor = BLANK,
            .spaceing = 0
        };

        bodyPartSlideBoxes[i] = (struct nSlideBox){
            .numberOfOptions = info->bodyPartsQuantity[i],
            .isActive = false,
            .currentOption = info->body[i],
            .init = {
                .x = (GetScreenWidth() >> 1) + 250,
                .y = (GetScreenHeight() >> 2) + i * spaceY,
                .incX = 5,
                .incY = 3,
                .posX = 1,
                .posY = 1,
                .width = 200
            },
            .font = &info->fonts[1],
            .fontSize = 20,
            .fontColor = BLACK,
            .color = GREEN,
            .borderActiveColor = RED,
            .borderColor = BLACK,
            .spaceing = 0
        };

        nCalculateSlideBoxPosition(&bodyPartSlideBoxes[i]);
        CalculateButtonPosition(&labels[i]);
    }

    CalculateTexturesPosition(info->bodyPosition, texturePosition);

    CalculateButtonPosition(&title);
    CalculateButtonPosition(&confirm);
    CalculateButtonPosition(&goBack);

    while (!WindowShouldClose() && *state == CHARACTER_CREATOR) {
        BeginDrawing();
            ClearBackground(color);

            DrawButton(title);
            DrawButton(confirm);
            DrawButton(goBack);

            for (int i = 0; i < 10; i++) {
                DrawButton(labels[i]);
                nDrawSlideBox(&bodyPartSlideBoxes[i]);

                int bodyPartIndex = bodyPartSlideBoxes[i].currentOption;
                DrawTextureEx(*info->bodyParts[i][bodyPartIndex], texturePosition[i], 0, 0.5, WHITE);
            }
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseOver(goBack)) {
                *state = NEW_GAME;
            }
            else if (isMouseOver(confirm)) {
                for (int i = 0; i < 10; i++) {
                    info->body[i] = bodyPartSlideBoxes[i].currentOption;
                }
                *state = NEW_GAME;
            }
        }

        for (int i = 0; i < 10; i++) {
            nUpdateSlideBox(&bodyPartSlideBoxes[i]);
        }
    }
}