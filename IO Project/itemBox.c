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

void DrawItem(int b, int a, int c, Rectangle itemBox, const struct playInfo *info) {
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
            min1 = itemBox.width / info->resources->weapons[a].width;
            min2 = itemBox.height / info->resources->weapons[a].height;

            DrawTextureEx(info->resources->weapons[a], texturePosition, 0.0f, min1 < min2 ? min1 : min2, WHITE);
            break;
        case 2:
            min1 = itemBox.width / info->resources->armorPart[a][c][0].width;
            min2 = itemBox.height / info->resources->armorPart[a][c][0].height;

            DrawTextureEx(info->resources->armorPart[a][c][0], texturePosition, 0.0f, min1 < min2 ? min1 : min2, WHITE);
            break;
        case 3:
            DrawTextureEx(info->resources->items[a], texturePosition, 0.0f, itemBox.width / info->resources->items[a].width, WHITE);
    }
}