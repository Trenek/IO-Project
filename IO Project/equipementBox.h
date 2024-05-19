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

void InitializeEquipementBox(struct equipementBox *element);

inline void UpdateEquipementBox(struct equipementBox* element) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        element->activeItem = -1;
        for (int i = 0; i < 25; i++) {
            if (isMouseOverItemBox(element->items[i])) {
                element->activeItem = i;
            }
        }
        if (element->activeItem == -1) { //nie kliknieto na zaden item, sprawdzamy czy kliknieto na itemType
            element->activeItemType = -1;
            for (int i = 0; i < 7; i++) {
                if (isMouseOverItemBox(element->itemTypes[i])) {
                    element->activeItemType = i;
                }
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