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

    for (int i = 0; i < 7; i++) {
        element->itemTypes[i] = (struct itemBox){
            .isActive = false,
            .init = {
                .x = element->x + 30 + (10 + 42) * i,
                .y = element->y + 60,
                .width = 42,
                .height = 30
            },
            .color = GRAY,
            .activeColor = DARKGRAY,
            .borderColor = BLACK
        };
        CalculateItemBoxPosition(&(element->itemTypes[i]));
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
        element.items[i].isActive = i == element.activeItem;
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
    for (int i = 0; i < 7; i++) {
        element.itemTypes[i].isActive = i == element.activeItemType;
        DrawItemBox(element.itemTypes[i]);
    }
}