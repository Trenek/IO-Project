#include "itemBox.h"
#include "playState.h"

void CalculateItemBoxPosition(struct itemBox *const element) {
    struct itemBoxPositionParameters initial = element->init;

    element->isActive = false;

    element->boxRectangle = (Rectangle){
        .x = initial.x - initial.posX * initial.width / 2.0f,
        .y = initial.y - initial.posY * initial.height / 2.0f,
        .width =  (float)initial.width,
        .height = (float)initial.height
    };
}

void DrawItemBox(const struct itemBox element) {
    DrawRectangleRec(element.boxRectangle, element.isActive ? element.activeColor : element.color);
    DrawRectangleLinesEx(element.boxRectangle, 1, element.borderColor);
}

void DrawItem(int a, int b, int c, Rectangle itemBox, const struct playInfo *info) {
    Vector2 texturePosition = {
        .x = itemBox.x,
        .y = itemBox.y
    };
    float min1 = 0;
    float min2 = 0;

    switch (a) {
        case 0:
            break;
        case 1:
            min1 = itemBox.width / info->resources->weapons[b].width;
            min2 = itemBox.height / info->resources->weapons[b].height;

            DrawTextureEx(info->resources->weapons[b], texturePosition, 0.0f, min1 < min2 ? min1 : min2, WHITE);
            break;
        case 2:
            min1 = itemBox.width / info->resources->armorPart[b][c][0].width;
            min2 = itemBox.height / info->resources->armorPart[b][c][0].height;

            DrawTextureEx(info->resources->armorPart[b][c][0], texturePosition, 0.0f, min1 < min2 ? min1 : min2, WHITE);
            break;
        case 3:
            DrawTextureEx(info->resources->items[b], texturePosition, 0.0f, itemBox.width / info->resources->items[b].width, WHITE);
    }
}