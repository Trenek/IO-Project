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
    
    int (*itemsID)[3];
    struct itemBox items[25];
    struct itemBox itemTypes[7];
    int (*armorPart)[9];
    int *weapon;
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
    int * const info = element->itemsID[element->activeItem];

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

    }
}

inline void Delete(struct equipementBox* element) {
    element->itemsID[element->activeItem][0] = 0;
}

void DrawEquipementBox(struct equipementBox element, struct playInfo *info);
#endif