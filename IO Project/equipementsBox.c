#include "playState.h"

#include "equipementBox.h"

void InitializeEquipementBox(struct equipementBox *element) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            element->items[i * 5 + j] = (struct itemBox){
                .isActive = false,
                .init = {
                    .x = element->x + 30 + (10 + element->itemBoxSize) * i,
                    .y = element->y + 150 + (10 + element->itemBoxSize) * j,
                    .width = element->itemBoxSize,
                    .height = element->itemBoxSize
                },
                .color = GRAY,
                .activeColor = DARKGRAY,
                .borderColor = BLACK
            };
            CalculateItemBoxPosition(&(element->items[i * 5 + j]));
        }
    }

    for (int i = 0; i < 6; i++) {
        element->equipedItems[i] = (struct itemBox){
            .isActive = false,
            .init = {
                .x = element->x + 30 + (10 + element->itemBoxSize) * i,
                .y = element->y + 30,
                .width = element->itemBoxSize,
                .height = element->itemBoxSize
            },
            .color = GRAY,
            .activeColor = DARKGRAY,
            .borderColor = BLACK
        };
        CalculateItemBoxPosition(&(element->equipedItems[i]));
    }

    for (int i = 0; i < 4; i++) {
        element->equipedItems[i + 6] = (struct itemBox){
            .isActive = false,
            .init = {
                .x = element->x + 30 + (10 + element->itemBoxSize) * i,
                .y = element->y + 30 + element->itemBoxSize + 10,
                .width = element->itemBoxSize,
                .height = element->itemBoxSize
            },
            .color = GRAY,
            .activeColor = DARKGRAY,
            .borderColor = BLACK
        };
        CalculateItemBoxPosition(&(element->equipedItems[i + 6]));
    }
}

void DrawEquipementBox(struct equipementBox element, struct playInfo *info) {
    Vector2 texturePosition;

    DrawRectangle(element.x, element.y, element.width, element.height, GRAY);
    for (int i = 0; i < 25; i++) {
        texturePosition = (Vector2){
            .x = element.items[i].boxRectangle.x,
            .y = element.items[i].boxRectangle.y
        };
        element.items[i].isActive = element.activeItemType == 0 && i == element.activeItem;
        DrawItemBox(element.items[i]);

        switch (element.itemsID[i][0]) {
            case 0:
                break;
            case 1:
                break;
            case 2:
                float min1 = element.items[i].boxRectangle.width / info->armorPart[element.itemsID[i][1]][element.itemsID[i][2]][0].width;
                float min2 = element.items[i].boxRectangle.height / info->armorPart[element.itemsID[i][1]][element.itemsID[i][2]][0].height;
                DrawTextureEx(info->armorPart[element.itemsID[i][1]][element.itemsID[i][2]][0], texturePosition, 0.0f, min1 < min2 ? min1 : min2, WHITE);
                break;
            case 3:
                DrawTextureEx(info->items[element.itemsID[i][1]], texturePosition, 0.0f, element.items[i].boxRectangle.width / info->items[element.itemsID[i][1]].width, WHITE);
                break;
        }
    }
    for (int i = 0; i < 9; i++) {
        texturePosition = (Vector2){
            .x = element.equipedItems[i].boxRectangle.x,
            .y = element.equipedItems[i].boxRectangle.y
        };
        float min1 = element.equipedItems[i].boxRectangle.width / info->armorPart[i][(*element.armorPart)[i]][0].width;
        float min2 = element.equipedItems[i].boxRectangle.height / info->armorPart[i][(*element.armorPart)[i]][0].height;
        element.equipedItems[i].isActive = element.activeItemType == 1 && i == element.activeItem;
        DrawItemBox(element.equipedItems[i]);
        if ((*element.armorPart)[i] != -1)
            DrawTextureEx(info->armorPart[i][(*element.armorPart)[i]][0], texturePosition, 0.0f, min1 < min2 ? min1 : min2, WHITE);
    }

    int i = 9;
    texturePosition = (Vector2){
        .x = element.equipedItems[i].boxRectangle.x,
        .y = element.equipedItems[i].boxRectangle.y
    };
    element.equipedItems[i].isActive = element.activeItemType == 1 && i == element.activeItem;
    DrawItemBox(element.equipedItems[i]);
    if (*element.weapon != -1) {
        float min1 = element.equipedItems[i].boxRectangle.width / info->weapons[*element.weapon].width;
        float min2 = element.equipedItems[i].boxRectangle.height / info->weapons[*element.weapon].height;

        DrawTextureEx(info->weapons[*element.weapon], texturePosition, 0.0f, min1 < min2 ? min1 : min2, WHITE);
    }
}