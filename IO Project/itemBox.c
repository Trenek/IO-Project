#include "itemBox.h"

void CalculateItemBoxPosition(struct itemBox* element) {
    struct itemBoxPositionParameters initial = element->init;

    element->boxRectangle = (Rectangle){
        .x = (float)initial.x - initial.width / 2,
        .y = (float)initial.y - initial.height / 2,
        .width =  (float)initial.width,
        .height = (float)initial.height
    };
}

void DrawItemBox(struct itemBox element) {
    DrawRectangleRec(element.boxRectangle, element.isActive ? element.activeColor : element.color);
    DrawRectangleLinesEx(element.boxRectangle, 1, element.borderColor);

    //TODO: draw items
}