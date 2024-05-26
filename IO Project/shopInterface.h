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
    int (*playerItemsID)[3];
    int (*sellerItemsID)[3];

    int *equipmentActiveType;
    int *equipmentActiveItem;

    union {
        struct shopInterfacePositionParameters init;
        struct {
            int width;

            RenderTexture2D toDraw;
            Vector2 leftCorner;
            Vector2 leftShopperCoordinate;

            Rectangle rec;

            int activeItem;

            struct itemBox items[10];

            int (*priceItem)[3];
            struct itemBox price;

            struct button buy;
            struct button sell;
        };
    };
};

void InitializeShopInterface(struct shopInterface *const element);
void DrawShopInterface(const struct shopInterface *const element, const struct playInfo *info);
void UpdateShopInterface(struct shopInterface *const element, const struct playInfo *info);
void UnloadShopInterface(struct shopInterface *const element);

#endif