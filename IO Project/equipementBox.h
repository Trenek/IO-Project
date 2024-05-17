#pragma once
#ifndef EQUIPEMENTBOX_H
#define EQUIPEMENTBOX_H

#include "itemBox.h"
#include <raylib.h>

struct equipementBox {
    int x;
    int y;
    int width;
    int height;
    int activeItemType;
    int activeItem;
    int itemBoxSize;
    
    struct itemBox items[25];
    struct itemBox itemTypes[7];
};

inline void InitializeEquipementBox(struct equipementBox *element) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            element->items[i * 5 + j].isActive = false;
            element->items[i * 5 + j].init.x = element->x + 30 + (10 + element->itemBoxSize) * i;
            element->items[i * 5 + j].init.y = element->y + 150 + (10 + element->itemBoxSize) * j;
            element->items[i * 5 + j].init.incX = 10;
            element->items[i * 5 + j].init.incY = 10;
            element->items[i * 5 + j].init.width = element->itemBoxSize;
            element->items[i * 5 + j].init.height = element->itemBoxSize;
            element->items[i * 5 + j].color = GRAY;
            element->items[i * 5 + j].activeColor = DARKGRAY;
            element->items[i * 5 + j].borderColor = BLACK;
            element->items[i * 5 + j].spaceing = 0;
        }
    }

    for (int i = 0; i < 7; i++) {
        element->itemTypes[i].isActive = false;
        element->itemTypes[i].init.x = element->x + 30 + (10 + 42) * i;
        element->itemTypes[i].init.y = element->y + 60;
        element->itemTypes[i].init.incX = 10;
        element->itemTypes[i].init.incY = 10;
        element->itemTypes[i].init.width = 42;
        element->itemTypes[i].init.height = 30;
        element->itemTypes[i].color = GRAY;
        element->itemTypes[i].activeColor = DARKGRAY;
        element->itemTypes[i].borderColor = BLACK;
        element->itemTypes[i].spaceing = 0;
    }

    for (int i = 0; i < 25; i++) {
        CalculateItemBoxPosition(&(element->items[i]));
    }
    for (int i = 0; i < 7; i++) {
        CalculateItemBoxPosition(&(element->itemTypes[i]));
    }
}

inline void UpdateEquipementBox(struct equipementBox* element) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        for (int i = 0; i < 25; i++) {
            if (isMouseOverItemBox(element->items[i])) {
                element->activeItem = i;
            }
        }
        for (int i = 0; i < 7; i++) {
            if (isMouseOverItemBox(element->itemTypes[i])) {
                element->activeItemType = i;
            }
        }
    }
}

inline void Equip(struct equipementBox* element) {
    //TODO: Equip element->items[element->activeItem]

    if (element == element); //uzycie element zeby sie skompilowalo xD
}

inline void Delete(struct equipementBox* element) {
    //TODO: Delete element->items[element->activeItem]
    if (element == element);
}

void DrawEquipementBox(struct equipementBox element);
#endif