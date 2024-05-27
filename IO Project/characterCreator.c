#include <raylib.h>

#include "state.h"
#include "playState.h"
#include "load.h"

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
    const char* bodyPartsNamesInPolish[10] = {
        [HEAD] = "G³owa",
        [LEFT_ARM] = "Lewe ramiê",
        [RIGHT_ARM] = "Prawie ramiê",
        [LEFT_FOOT] = "Lewa stopa",
        [RIGHT_FOOT] = "Prawa stopa",
        [LEFT_HAND] = "Lewa d³oñ",
        [RIGHT_HAND] = "Prawa d³oñ",
        [LEFT_LEG] = "Lewa noga",
        [RIGHT_LEG] = "Prawa d³oñ",
        [TORSO] = "Tors"
    };
    
    const int numberOfOptions[10] = {
        [HEAD] = 4,
        [LEFT_ARM] = 1,
        [RIGHT_ARM] = 1,
        [LEFT_FOOT] = 1,
        [RIGHT_FOOT] = 1,
        [LEFT_HAND] = 1,
        [RIGHT_HAND] = 1,
        [LEFT_LEG] = 1,
        [RIGHT_LEG] = 1,
        [TORSO] = 1
    };

    int bodyPosition[4][10][2];
    int width, height;
    Vector2 texturePosition[10];
    Texture2D(*bodyPartsTextures[10])[4];

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
        .text = "ZatwierdŸ",
        .isActive = 1,
        .init = {
            .x = (GetScreenWidth() >> 1) - spaceX,
            .y = (GetScreenHeight() >> 2) + 11 * spaceY,
            .incX = 10,
            .incY = 10,
            .posX = 1,
            .posY = 1
        },
        .font = &info->fonts[0],
        .fontSize = 20,
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
    }
    
    struct slideBox **bodyPartSlideBoxes = malloc(10 * sizeof(struct slideBox*));
    for (int i = 0; i < 10; i++) {
        bodyPartSlideBoxes[i] = malloc(sizeof(struct slideBox) + numberOfOptions[i] * sizeof(char *));
        *bodyPartSlideBoxes[i] = (struct slideBox){
            .numberOfOptions = numberOfOptions[i],
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
        for (int j = 0; j < numberOfOptions[i]; j++) {
            bodyPartSlideBoxes[i]->options[j] = malloc(3 * sizeof(char));
            snprintf((char*)bodyPartSlideBoxes[i]->options[j], 3, "%d", j + 1);
        }
    }

    loadBodyPosition(&width, &height, bodyPosition);
    CalculateTexturesPosition(bodyPosition, texturePosition);

    loadBodyParts(bodyPartsTextures);

    CalculateButtonPosition(&title);
    CalculateButtonPosition(&confirm);
    CalculateButtonPosition(&goBack);

    for (int i = 0; i < 10; i++) {
        CalculateButtonPosition(&labels[i]);
        CalculateSlideBoxPosition(bodyPartSlideBoxes[i]);
    }


    while (!WindowShouldClose() && *state == CHARACTER_CREATOR) {
        BeginDrawing();
        ClearBackground(color);

        DrawButton(title);
        DrawButton(confirm);
        DrawButton(goBack);

        for (int i = 0; i < 10; i++) {
            DrawButton(labels[i]);
            DrawSlideBox(bodyPartSlideBoxes[i]);

            int bodyPartIndex = bodyPartSlideBoxes[i]->currentOption;
            DrawTextureEx(*bodyPartsTextures[i][bodyPartIndex], texturePosition[i], 0, 0.5, WHITE);
        }
        
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseOver(goBack)) {
                *state = NEW_GAME;
            }
            else if (isMouseOver(confirm)) {
                for (int i = 0; i < 10; i++) {
                    info->body[i] = bodyPartSlideBoxes[i]->currentOption;
                }
                *state = NEW_GAME;
            }
        }

        for (int i = 0; i < 10; i++) {
            UpdateSlideBox(bodyPartSlideBoxes[i]);
        }
    }
    for (int i = 0; i < 10; ++i) {
        free(bodyPartSlideBoxes[i]);
    }
    free(bodyPartSlideBoxes);
    unloadBodyParts(bodyPartsTextures);
}