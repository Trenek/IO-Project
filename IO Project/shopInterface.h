#ifndef SHOPINTERFACE_H
#define SHOPINTERFACE_H

#include <raylib.h>

#include "itemBox.h"
#include "button.h"

struct shopInterfacePositionParameters {
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

struct shopInterface {
    Texture2D *seller;
    int(*itemsID)[3];

    union {
        struct shopInterfacePositionParameters init;
        struct {
            Rectangle rec;
            Vector2 leftShopperCoordinate;

            int activeItem;

            struct itemBox items[10];

            struct button buy;
            struct button sell;
        };
    };
};

void InitializeShopInterface(struct shopInterface *const element);
void DrawShopInterface(struct shopInterface *const element, struct playInfo *info);
bool UpdateShopInterface(struct shopInterface *const element, struct playInfo *info);

#endif