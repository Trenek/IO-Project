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
        .isActive = 0,
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
        .isActive = 0,
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

    element->price = (struct itemBox){
        .init = {
            .x = (int)element->leftCorner.x + 3 * init.itemBoxSize + 4 * (init.itemBoxSize + init.gapSize),
            .y = (int)element->leftCorner.y + 3 * (init.gapSize + init.itemBoxSize),
            .posX = 0,
            .posY = 0,
            .width = init.itemBoxSize,
            .height = init.itemBoxSize
        },
        .color = BLUE,
        .activeColor = DARKGRAY,
        .borderColor = BLACK
    };
    CalculateItemBoxPosition(&element->price);

    element->priceItem = NULL;

    DrawToRenderTexture(element);
}

int (*getPrice(int (*item)[3], const struct playInfo *info))[3] {
    int (*result)[3] = NULL;

    switch ((*item)[0]) {
        case 0:
            break;
        case 1:
            result = &info->weaponPrice[(*item)[1]];
            break;
        case 2:
            result = &info->armorPrice[(*item)[1]][(*item)[2]];
            break;
        case 3:
            result = &info->itemsPrice[(*item)[1]];
            break;
    }

    return result;
}

void DrawShopInterface(const struct shopInterface *const element, const struct playInfo *info) {
    int i = 0;

    DrawTextureEx(element->toDraw.texture, element->leftCorner, 0.0f, 1.0f, WHITE);

    while (i < 10) {
        DrawItemBox(element->items[i]);
        DrawItem(element->sellerItemsID[i][0], element->sellerItemsID[i][1], element->sellerItemsID[i][2], element->items[i].boxRectangle, info);

        i += 1;
    }
    DrawItemBox(element->price);
    
    if (element->priceItem != NULL) {
        DrawItem((*element->priceItem)[0], (*element->priceItem)[1], (*element->priceItem)[2], element->price.boxRectangle, info);
    }

    DrawButton(element->buy);
    DrawButton(element->sell);
}

int findElement(int (*playerEquipment)[3], int(*wantedItem)[3]) {
    int result = -1;
    int i = 0;

    while (i < 25 && result == -1) {
        if (playerEquipment[i][0] == (*wantedItem)[0])
        switch ((*wantedItem)[0]) {
            case 0:
                result = i;
                break;
            case 1:
            case 3:
                if (playerEquipment[i][1] == (*wantedItem)[1]) {
                    result = i;
                }
                break;
            case 2:
                if (playerEquipment[i][1] == (*wantedItem)[1]) 
                if (playerEquipment[i][2] == (*wantedItem)[2]) {
                    result = i;
                }
                break;
        }

        i += 1;
    }

    return result;
}

void UpdateShopInterface(struct shopInterface *const element, const struct playInfo *info) {
    int i = 0;

    if (isMouseOver(element->buy)) {
        i = findElement(element->playerItemsID, element->priceItem);
        element->playerItemsID[i][0] = element->sellerItemsID[element->activeItem][0];
        element->playerItemsID[i][1] = element->sellerItemsID[element->activeItem][1];
        element->playerItemsID[i][2] = element->sellerItemsID[element->activeItem][2];

        element->priceItem = NULL;
        element->sellerItemsID[element->activeItem][0] = 0;
    }
    else if (isMouseOver(element->sell)) {
        element->playerItemsID[*element->equipmentActiveItem][0] = (*element->priceItem)[0];
        element->playerItemsID[*element->equipmentActiveItem][1] = (*element->priceItem)[1];
        element->playerItemsID[*element->equipmentActiveItem][2] = (*element->priceItem)[2];

        element->priceItem = NULL;
    }

    element->activeItem = -1;
    i = 0;
    while (i < 10) {
        element->items[i].isActive = isMouseOverItemBox(element->items[i]);
        if (element->items[i].isActive) {
            element->activeItem = i;
        }

        i += 1;
    }

    if (element->activeItem != -1) {
        element->priceItem = getPrice(&element->sellerItemsID[element->activeItem], info);
    }
    else if (*element->equipmentActiveType == 0) {
        element->priceItem = getPrice(&element->playerItemsID[*element->equipmentActiveItem], info);
    }

    element->sell.isActive = (*element->equipmentActiveType != 0) ? 0 : 1;
    element->buy.isActive = (element->activeItem == -1) ? 0 : findElement(element->playerItemsID, element->priceItem) == -1 ? 0 : 1;
}

void UnloadShopInterface(struct shopInterface *const element) {
    UnloadRenderTexture(element->toDraw);
}
