#include <raylib.h>
#include "playState.h"
#include "button.h"
#include "equipementBox.h"

#define INC_Y (10)
#define INC_X (10)
#define FONT_SIZE (25)

void shop(enum playState* state, struct playInfo* info) {
    const int height = (GetScreenHeight() >> 1) + 80;
    const int space = FONT_SIZE + INC_Y * 2 + 10;
    const int size = 400;

    Color color1 = { .r = 100, .g = 100, .b = 100, .a = 200 };
    Color color2 = { .r = 0, .g = 0, .b = 0, .a = 60 };

    struct button title = {
        .text = "Sklep",
        .isActive = 1,
        .init = {
            .x = GetScreenWidth() >> 1,
            .y = 50,
            .incX = 10,
            .incY = 10,
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
    struct button equip = {
        .text = "Wyposaż",
        .isActive = 1,
        .init = {
            .x = GetScreenWidth() - size / 2 - 70,
            .y = height - space,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1
        },
        .font = &info->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = DARKGRAY,
        .hoverColor = color2,
        .spaceing = 0
    };
    struct button destroy = {
        .text = "Zniszcz",
        .isActive = 1,
        .init = {
            .x = GetScreenWidth() - size / 2 - 70,
            .y = height,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1
        },
        .font = &info->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = DARKGRAY,
        .hoverColor = color2,
        .spaceing = 0
    };
    struct button goBack = {
        .text = "Powrót",
        .isActive = 1,
        .init = {
            .x = GetScreenWidth() - size / 2 - 70,
            .y = height + 2 * space,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1
        },
        .font = &info->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = DARKGRAY,
        .hoverColor = color2,
        .spaceing = 0
    };
    struct equipementBox equipement = {
        .init = {
            .x = (GetScreenWidth() - size) >> 1,
            .y = ((GetScreenHeight() - size) >> 1) + 50,
            .posX = 1,
            .posY = 1,
            .itemBoxSize = 40
        },
        .itemsID = info->player.equipment,
        .armorPart = &info->player.character.armorPart,
        .weapon = &info->player.character.weapon
    };

    CalculateButtonPosition(&title);
    CalculateButtonPosition(&equip);
    CalculateButtonPosition(&destroy);
    CalculateButtonPosition(&goBack);
    InitializeEquipementBox(&equipement);

    while (*state == SHOP && !WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(color1);
        if (info->screenCamera != NULL) {
            DrawTextureRec(info->screenCamera->texture, *info->screenRect, (Vector2) { 0, 0 }, WHITE);
        }
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight() + 100, color1);

        DrawEquipementBox(&equipement, info);
        DrawButton(title);
        DrawButton(equip);
        DrawButton(destroy);
        DrawButton(goBack);

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseOver(goBack)) *state = DIALOG;

            UpdateEquipementBox(&equipement, info);
        }
    }
}