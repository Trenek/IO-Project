#ifndef EQUIPEMENTBOX_H
#define EQUIPEMENTBOX_H

#include "itemBox.h"
#include <raylib.h>

struct equipementBox {
    int x;
    int y;
    int width;
    int height;
    int itemBoxSize;

    int activeItemType;
    int activeItem;
    
    int (*itemsID)[3];
    struct itemBox items[25];
    struct itemBox equipedItems[10];
    int (*armorPart)[9];
    int *weapon;
};

void InitializeEquipementBox(struct equipementBox *element);

inline void UpdateEquipementBox(struct equipementBox* element) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        element->activeItemType = -1;
        for (int i = 0; i < 25; i++) {
            if (isMouseOverItemBox(element->items[i])) {
                element->activeItemType = 0;
                element->activeItem = i;
            }
        }
        if (element->activeItemType == -1) { //nie kliknieto na zaden item, sprawdzamy czy kliknieto na itemType
            for (int i = 0; i < 10; i++) {
                if (isMouseOverItemBox(element->equipedItems[i])) {
                    element->activeItemType = 1;
                    element->activeItem = i;
                }
            }
        }
    }
}

inline void Equip(struct equipementBox* element) {
    if (element->activeItemType == 0) {
        int *const info = element->itemsID[element->activeItem];

        if (info[0] == 2) {
            if ((*element->armorPart)[info[1]] == -1) {
                (*element->armorPart)[info[1]] = info[2];
                info[0] = 0;
            }
            else {
                int temp = info[2];
                info[2] = (*element->armorPart)[info[1]];
                (*element->armorPart)[info[1]] = temp;
            }
        }
        else if (info[0] == 3) {
            if (*element->weapon == -1) {
                *element->weapon = info[2];
                info[0] = 0;
            }
            else {
                int temp = info[2];
                info[2] = *element->weapon;
                *element->weapon = temp;
            }
        }
    }
}

inline void Delete(struct equipementBox *element) {
    if (element->activeItemType == 0) {
        element->itemsID[element->activeItem][0] = 0;
    }
    else {
        if (element->activeItem < 9) {
            (*element->armorPart)[element->activeItem] = -1;
        }
        else {
            *element->weapon = -1;
        }
    }
}

void DrawEquipementBox(struct equipementBox element, struct playInfo *info);
#endif