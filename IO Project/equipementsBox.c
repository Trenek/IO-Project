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

void DrawEquipementBox(struct equipementBox element) {
    DrawRectangle(element.x, element.y, element.width, element.height, GRAY);
    for (int i = 0; i < 25; i++) {
        element.items[i].isActive = i == element.activeItem;
        DrawItemBox(element.items[i]);
    }
    for (int i = 0; i < 7; i++) {
        element.itemTypes[i].isActive = i == element.activeItemType;
        DrawItemBox(element.itemTypes[i]);
    }
}