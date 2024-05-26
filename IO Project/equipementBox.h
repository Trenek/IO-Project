#ifndef EQUIPEMENTBOX_H
#define EQUIPEMENTBOX_H

#include <raylib.h>

#include "itemBox.h"
#include "button.h"

struct equipementBoxPositionParameters {
    int x;
    int y;
    int posX;
    int posY;

    int gapSize;
    int itemBoxSize;

    Font *buttonFont;
    int buttonIncX;
    int buttonIncY;
};

struct equipementBox {
    union {
        struct equipementBoxPositionParameters init;
        struct {
            Rectangle rec;
            Vector2 playerPosition;

            int activeItemType;
            int activeItem;

            struct itemBox items[25];
            struct itemBox equipedItems[10];

            struct button equip;
            struct button unequip;
            struct button destroy;

            struct button goBack;
        };
    };
    
    int (*playerItemsID)[3];
    int (*armorPart)[9];
    int *weapon;
};

void InitializeEquipementBox(struct equipementBox *const element);
void DrawEquipementBox(const struct equipementBox *const element, struct playInfo *info);
bool UpdateEquipementBox(struct equipementBox *const element, struct playInfo *info);

#endif