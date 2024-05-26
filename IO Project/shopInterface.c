#include "playState.h"

#include "shopInterface.h"
#include "button.h"

static void DrawToRenderTexture(const struct shopInterface *const element) {
    RenderTexture2D temp = LoadRenderTexture(element->toDraw.texture.width, element->toDraw.texture.height);

    BeginTextureMode(temp);
    ClearBackground(GRAY);
    DrawRectangleLines(0, 0, element->toDraw.texture.width, element->toDraw.texture.height, WHITE);

    DrawTextureEx(*element->seller, element->leftShopperCoordinate, 0, (float)element->width / element->seller->width, WHITE);

    DrawRectangleRec(element->rec, BLUE);
    EndTextureMode();

    BeginTextureMode(element->toDraw);
    DrawTextureEx(temp.texture, (Vector2) { 0, 0 }, 0.0f, 1.0f, WHITE);
    EndTextureMode();

    UnloadRenderTexture(temp);
}

void InitializeShopInterface(struct shopInterface *const element) {
    const struct shopInterfacePositionParameters init = element->init;
    const int height = init.itemBoxSize * 10 + init.gapSize * 5;
    const int width = init.itemBoxSize * 9 + init.gapSize * 4;
    
    element->width = init.itemBoxSize * 5 + init.gapSize * 4;
    element->toDraw = LoadRenderTexture(width, height);

    element->leftCorner = (Vector2) {
        .x = init.x - init.posX * width / 2.0f,
        .y = init.y - init.posY * height / 2.0f
    };

    element->rec = (Rectangle){
        .x = 0,
        .y = height - 2.0f * (init.gapSize + init.itemBoxSize) - init.gapSize,
        .height = (float)height,
        .width = (float)width
    };

    element->leftShopperCoordinate = (Vector2) {
        .x = 1.0f * init.itemBoxSize,
        .y = (float)init.itemBoxSize,
    };

    element->buy = (struct button){
        .text = "Kup",
        .isActive = 1,
        .init = {
            .x = (int)element->leftCorner.x + 1 * init.itemBoxSize + 5 * (init.gapSize + init.itemBoxSize),
            .y = (int)element->leftCorner.y + height - 2 * (init.gapSize + init.itemBoxSize),
            .incX = init.buttonIncX,
            .incY = init.buttonIncY,
            .posX = 0,
            .posY = 0
        },
        .font = init.buttonFont,
        .fontSize = init.itemBoxSize - 2 * init.buttonIncY,
        .fontColor = BLACK,
        .color = GRAY,
        .hoverColor = BLANK,
        .spaceing = 0
    };
    element->sell = (struct button){
        .text = "Sprzedaj",
        .isActive = 1,
        .init = {
            .x = (int)element->leftCorner.x + 1 * init.itemBoxSize + 5 * (init.gapSize + init.itemBoxSize),
            .y = (int)element->leftCorner.y + height - (init.gapSize + init.itemBoxSize),
            .incX = init.buttonIncX,
            .incY = init.buttonIncY,
            .posX = 0,
            .posY = 0
        },
        .font = init.buttonFont,
        .fontSize = init.itemBoxSize - 2 * init.buttonIncY,
        .fontColor = BLACK,
        .color = GRAY,
        .hoverColor = BLANK,
        .spaceing = 0
    };

    CalculateButtonPosition(&element->buy);
    CalculateButtonPosition(&element->sell);

    element->sell;

    for (int i = 0; i < 10; i++) {
        element->items[i] = (struct itemBox){
            .init = {
                .x = (int)element->leftCorner.x + 1 * init.itemBoxSize + (i % 5) * (init.gapSize + init.itemBoxSize),
                .y = (int)element->leftCorner.y + height - 2 * (init.gapSize + init.itemBoxSize) + (i / 5) * (init.gapSize + init.itemBoxSize),
                .posX = 0,
                .posY = 0,
                .width = init.itemBoxSize,
                .height = init.itemBoxSize
            },
            .color = GRAY,
            .activeColor = DARKGRAY,
            .borderColor = BLACK
        };
        CalculateItemBoxPosition(&(element->items[i]));
    }

    DrawToRenderTexture(element);
}

void DrawShopInterface(const struct shopInterface *const element, const struct playInfo *info) {
    int i = 0;

    DrawTextureEx(element->toDraw.texture, element->leftCorner, 0.0f, 1.0f, WHITE);

    while (i < 10) {
        DrawItemBox(element->items[i]);
        DrawItem(element->sellerItemsID[i][0], element->sellerItemsID[i][1], element->sellerItemsID[i][2], element->items[i].boxRectangle, info);

        i += 1;
    }

    DrawButton(element->buy);
    DrawButton(element->sell);
}

void UpdateShopInterface(struct shopInterface *const element) {
    element->activeItem = -1;

    for (int i = 0; i < 10; i++) {
        element->items[i].isActive = isMouseOverItemBox(element->items[i]);
        if (element->items[i].isActive) {
            element->activeItem = i;
        }
    }

    element->sell.isActive = (*element->equipmentActiveType == -1) ? 0 : 1;
    element->buy.isActive = (element->activeItem == -1) ? 0 : 1;
}

void UnloadShopInterface(struct shopInterface *const element) {
    UnloadRenderTexture(element->toDraw);
}
