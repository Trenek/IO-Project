#include <raylib.h>

#include "playState.h"

#include "menuElements.h"

#define INC_Y (10)
#define INC_X (10)
#define FONT_SIZE (25)

void shop(enum playState *state, struct playInfo *info) {
    Color color1 = { .r = 100, .g = 100, .b = 100, .a = 200 };

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
        .font = &info->resources->fonts[0],
        .fontSize = 100,
        .fontColor = BLACK,
        .color = BLANK,
        .hoverColor = BLANK,
        .spaceing = 0
    };
    struct equipementBox equipement = {
        .init = {
            .x = (GetScreenWidth() >> 1),
            .y = GetScreenHeight() >> 1,
            .posX = 0,
            .posY = 1,
            .itemBoxSize = 40,
            .gapSize = 10,
            .buttonFont = &info->resources->fonts[0],
            .buttonIncX = 5,
            .buttonIncY = 5
        },
        .playerItemsID = info->save.player.equipment,
        .armorPart = &info->save.player.character.armorPart,
        .weapon = &info->save.player.character.weapon
    };

    struct shopInterface shopInterface = {
        .init = {
            .x = (GetScreenWidth() >> 1),
            .y = GetScreenHeight() >> 1,
            .posX = 2,
            .posY = 1,
            .itemBoxSize = 40,
            .gapSize = 10,
            .buttonFont = &info->resources->fonts[0],
            .buttonIncX = 5,
            .buttonIncY = 5
        },
        .equipmentActiveItem = &equipement.activeItem,
        .equipmentActiveType = &equipement.activeItemType,
        .seller = info->chosen.object.texture,
        .playerItemsID = info->save.player.equipment,
        .sellerItemsID = info->save.shopEquipment[info->chosenShop]
    };

    CalculateButtonPosition(&title);
    InitializeEquipementBox(&equipement);
    InitializeShopInterface(&shopInterface);

    while (!WindowShouldClose() && *state == SHOP) {
        BeginDrawing();
            ClearBackground(color1);

            if (info->screenCamera != NULL) {
                DrawTextureRec(info->screenCamera->texture, *info->screenRect, (Vector2) { 0, 0 }, WHITE);
            }
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight() + 100, color1);

            DrawEquipementBox(&equipement, info);
            DrawShopInterface(&shopInterface, info);
            DrawButton(title);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (UpdateEquipementBox(&equipement, info)) *state = DIALOG;

            UpdateShopInterface(&shopInterface, info);
        }
    }

    UnloadShopInterface(&shopInterface);
}