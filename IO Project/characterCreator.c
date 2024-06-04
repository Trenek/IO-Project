#include <raylib.h>

#include "state.h"
#include "playState.h"
#include "character.h"

#include "menuElements.h"

#define INC_Y (5)
#define INC_X (10)
#define FONT_SIZE (25)

void characterCreator(enum state *state, struct menuInfo *info) {  
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

    const int spaceY = INC_Y + INC_Y + FONT_SIZE;
    const int spaceX = 90;

    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };

    Texture2D texture = { 0 };
    struct character bob = {
        .bodyPart = { 0 },
        .object.texture = &texture,
        .direction = 0,
    };

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
        .font = &info->resources.fonts[0],
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
            .y = (GetScreenHeight() >> 2) + 11 * spaceY,
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

    struct button turnLeft = {
        .text = "<",
        .isActive = 1,
        .init = {
            .x = GetScreenWidth() >> 4,
            .y = (GetScreenHeight() >> 2) + 5 * spaceY,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1
        },
        .font = &info->resources.fonts[0],
        .fontSize = 40,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };

    struct button turnRight = {
        .text = ">",
        .isActive = 1,
        .init = {
            .x = (GetScreenWidth() >> 1) - spaceX,
            .y = (GetScreenHeight() >> 2) + 5 * spaceY,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1
        },
        .font = &info->resources.fonts[0],
        .fontSize = 40,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };

    struct button labels[10];
    struct nSlideBox bodyPartSlideBoxes[10];

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
            .font = &info->resources.fonts[0],
            .fontSize = FONT_SIZE,
            .fontColor = BLACK,
            .color = BLANK,
            .hoverColor = BLANK,
            .spaceing = 0
        };

        bodyPartSlideBoxes[i] = (struct nSlideBox){
            .numberOfOptions = info->resources.bodyPartsQuantity[i],
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
            .font = &info->resources.fonts[1],
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

    memcpy(bob.bodyPart, info->body, sizeof(int) * 10);
    memset(bob.armorPart, -1, sizeof(int) * 9);
    bob.weapon = -1;

    assemblePlayerTexture(&info->resources, &bob);

    Vector2 bobPosition = (Vector2){
       .x = GetScreenWidth() / 8.0f,
       .y = (GetScreenHeight() / 2.0f) - (texture.height / 4.0f)
    };

    CalculateButtonPosition(&title);
    CalculateButtonPosition(&confirm);
    CalculateButtonPosition(&goBack);
    CalculateButtonPosition(&turnLeft);
    CalculateButtonPosition(&turnRight);

    while (!WindowShouldClose() && *state == CHARACTER_CREATOR) {
        BeginDrawing();
            ClearBackground(color);

            DrawButton(title);
            DrawButton(confirm);
            DrawButton(goBack);
            DrawButton(turnLeft);
            DrawButton(turnRight);

            for (int i = 0; i < 10; i++) {
                DrawButton(labels[i]);
                nDrawSlideBox(&bodyPartSlideBoxes[i]);
            }
            DrawTextureEx(texture, bobPosition, 0.0f, 0.5f, WHITE);
        EndDrawing();
       
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseOver(goBack)) {
                *state = NEW_GAME;
            }
            else if (isMouseOver(confirm)) {
                memcpy(info->body, bob.bodyPart, sizeof(int) * 10);
                *state = NEW_GAME;
            }
            else if (isMouseOver(turnLeft)) {
                if (bob.direction == 0) {
                    bob.direction = 3;
                }
                else {
                    bob.direction -= 1;
                }
                assemblePlayerTexture(&info->resources, &bob);
            }
            else if (isMouseOver(turnRight)) {
                if (bob.direction == 3) {
                    bob.direction = 0;
                }
                else {
                    bob.direction += 1;
                }
                assemblePlayerTexture(&info->resources, &bob);
            }
        }

        for (int i = 0; i < 10; i++) {
            if (nUpdateSlideBox(&bodyPartSlideBoxes[i])) {
                bob.bodyPart[i] = bodyPartSlideBoxes[i].currentOption;
                assemblePlayerTexture(&info->resources, &bob);
            }
        }
    }

    UnloadTexture(texture);
}