#include "itemBox.h"

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