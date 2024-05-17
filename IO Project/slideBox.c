#include <string.h>

#include "slideBox.h"

void CalculateSelectionBoxPosition(struct slideBox *element) {
    Vector2 size = MeasureTextEx(*(element->font), element->options[element->currentOption], (float)element->fontSize, (float)element->spaceing);
    struct slideBoxPositionParameters init = element->init;

    element->boxRectangle = (Rectangle){
        .x = init.x - init.width / 2.0f,
        .y = init.y - init.posY * size.y / 2.0f - init.incY,
        .width = (float)init.width + (init.incX << 1),
        .height = size.y + (init.incY << 1)
    };
    element->boxLeftRectangle = (Rectangle){
        .x = element->boxRectangle.x - 40,
        .y = element->boxRectangle.y,
        .width = 40,
        .height = element->boxRectangle.height
    };
    element->boxRightRectangle = (Rectangle){
        .x = element->boxRectangle.x + element->boxRectangle.width,
        .y = element->boxRectangle.y,
        .width = 40,
        .height = element->boxRectangle.height
    };
}

void DrawSelectionBox(struct slideBox *element) {
    DrawRectangleRec(element->boxRectangle, element->color);
    DrawRectangleRec(element->boxLeftRectangle, element->color);
    DrawRectangleRec(element->boxRightRectangle, element->color);
    DrawRectangleLinesEx(element->boxRectangle, 1, element->isActive ? element->borderActiveColor : element->borderColor);
    DrawRectangleLinesEx(element->boxLeftRectangle, 1, element->isActive ? element->borderActiveColor : element->borderColor);
    DrawRectangleLinesEx(element->boxRightRectangle, 1, element->isActive ? element->borderActiveColor : element->borderColor);

    Vector2 size = MeasureTextEx(*(element->font), element->options[element->currentOption], (float)element->fontSize, (float)element->spaceing);
    Vector2 textPosition = (Vector2) {
        .x = element->boxRectangle.x + element->boxRectangle.width / 2 - size.x / 2,
        .y = element->boxRectangle.y
    };
    DrawTextEx(*(element->font), element->options[element->currentOption], textPosition, (float)element->fontSize, (float)element->spaceing, element->fontColor);
}

void InternalUpdateSelectionBox(struct slideBox *element) {
    if (IsKeyPressed(KEY_LEFT)) {
        if (element->currentOption == 0) {
            element->currentOption = element->numberOfOptions - 1;
        } else {
            element->currentOption -= 1;
        }
    }

    if (IsKeyPressed(KEY_RIGHT)) {
        element->currentOption += 1;
        element->currentOption %= element->numberOfOptions;
    }
}