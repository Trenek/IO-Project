#include "playState.h"

#include "shopInterface.h"
#include "button.h"

void InitializeShopInterface(struct shopInterface *const element) {
    const struct shopInterfacePositionParameters init = element->init;
    const float height = init.itemBoxSize * 10.0f + init.gapSize * 5;
    const float width = init.itemBoxSize * 9.0f + init.gapSize * 4;

    element->rec = (Rectangle){
        .x = init.x - init.posX * width / 2,
        .y = init.y - init.posY * height / 2,
        .width = width,
        .height = height
    };

    element->leftShopperCoordinate = (Vector2){
        .x = element->rec.x + init.itemBoxSize + 5 * (init.gapSize + init.itemBoxSize),
        .y = element->rec.y + init.itemBoxSize,
    };

    for (int i = 0; i < 10; i++) {
        element->items[i] = (struct itemBox){
            .init = {
                .x = (int)(element->rec.x) + init.itemBoxSize + (i % 5) * (init.gapSize + init.itemBoxSize),
                .y = (int)(element->rec.y) + init.itemBoxSize + (i / 5) * (init.gapSize + init.itemBoxSize),
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
}
/**
static void DrawItem(int b, int a, int c, Rectangle itemBox, struct playInfo *info) {
    Vector2 texturePosition = {
        .x = itemBox.x,
        .y = itemBox.y
    };
    float min1 = 0;
    float min2 = 0;

    switch (b) {
        case 0:
            break;
        case 1:
            min1 = itemBox.width / info->weapons[a].width;
            min2 = itemBox.height / info->weapons[a].height;

            DrawTextureEx(info->weapons[a], texturePosition, 0.0f, min1 < min2 ? min1 : min2, WHITE);
            break;
        case 2:
            min1 = itemBox.width / info->armorPart[a][c][0].width;
            min2 = itemBox.height / info->armorPart[a][c][0].height;

            DrawTextureEx(info->armorPart[a][c][0], texturePosition, 0.0f, min1 < min2 ? min1 : min2, WHITE);
            break;
        case 3:
            DrawTextureEx(info->items[a], texturePosition, 0.0f, itemBox.width / info->items[a].width, WHITE);
    }
}
/**/
void DrawShopInterface(struct shopInterface *const element, struct playInfo *info) {
    int i = 0;

    DrawRectangleRec(element->rec, GRAY);
    for (i = 0; i < 10; i++) {
        DrawItemBox(element->items[i]);
    }

    DrawTextureEx(*info->player.character.object.texture, element->leftShopperCoordinate, 0, 0.25f, WHITE);
}
/**
static void Equip(struct equipementBox *element) {
    int *const info = element->itemsID[element->activeItem];

    if (element->activeItemType == 0) {
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
        else if (info[0] == 1) {
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

int getFirstEmptyEquipmentSquare(struct equipementBox *element) {
    int result = -1;
    int i = 0;

    while (i < 25 && result == -1) {
        if (element->itemsID[i][0] == 0) {
            result = i;
        }

        i += 1;
    }

    return result;
}


static void Unequip(struct equipementBox *element) {
    int firstEmpty = getFirstEmptyEquipmentSquare(element);

    if (firstEmpty != -1)
        if (element->activeItem < 9) {
            element->itemsID[firstEmpty][0] = 2;
            element->itemsID[firstEmpty][1] = element->activeItem;
            element->itemsID[firstEmpty][2] = (*element->armorPart)[element->activeItem];

            (*element->armorPart)[element->activeItem] = -1;
        }
        else {
            element->itemsID[firstEmpty][0] = 1;
            element->itemsID[firstEmpty][1] = *element->weapon;

            (*element->armorPart)[element->activeItem] = -1;
        }
}

static void Delete(struct equipementBox *element) {
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

bool UpdateEquipementBox(struct equipementBox *const element, struct playInfo *info) {
    bool result = false;

    if (isMouseOver(element->activeItemType == 1 ? element->unequip : element->equip)) {
        if (element->activeItemType == 1) {
            Unequip(element);
        }
        else {
            Equip(element);
        }
        assemblePlayerTexture(info, &info->player.character);
    }
    else if (isMouseOver(element->destroy)) {
        Delete(element);
    }
    else if (isMouseOver(element->goBack)) {
        result = true;
    }

    element->activeItemType = -1;
    element->equip.isActive = 0;
    element->unequip.isActive = 0;
    element->destroy.isActive = 0;

    for (int i = 0; i < 25; i++) {
        element->items[i].isActive = isMouseOverItemBox(element->items[i]);
        if (element->items[i].isActive) {
            switch (element->itemsID[i][0]) {
                case 0:
                    break;
                case 1:
                case 2:
                    element->equip.isActive = 1;
                case 3:
                    element->destroy.isActive = 1;
                    break;
            }
            element->activeItemType = 0;
            element->activeItem = i;
        }
    }
    for (int i = 0; i < 10; i++) {
        element->equipedItems[i].isActive = isMouseOverItemBox(element->equipedItems[i]);
        if (element->equipedItems[i].isActive) {
            if (i < 9) {
                if ((*element->armorPart)[i] != -1) {
                    element->destroy.isActive = 1;
                    if (getFirstEmptyEquipmentSquare(element) != -1) {
                        element->unequip.isActive = 1;
                    }
                }
            }
            else {
                if (*element->weapon != -1) {
                    element->unequip.isActive = 1;
                    if (getFirstEmptyEquipmentSquare(element) != -1) {
                        element->destroy.isActive = 1;
                    }
                }
            }

            element->activeItemType = 1;
            element->activeItem = i;
        }
    }

    return result;
}
/**/