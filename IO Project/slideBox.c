#include <string.h>

#include "slideBox.h"

void CalculateSlideBoxPosition(struct slideBox *element) {
    struct slideBoxPositionParameters init = element->init;

    element->rect = (Rectangle){
        .x = init.x - init.posX * init.width / 2.0f,
        .y = init.y - init.posY * (element->fontSize + 2.0f * init.incY) / 2,
        .width = (float)init.width + init.incX * 2.0f,
        .height = element->fontSize + init.incY * 2.0f
    };
}

void DrawSlideBox(struct slideBox *element) {
    DrawRectangleRec(element->rect, element->color);
    DrawRectangleLinesEx(element->rect, 1, element->isActive ? element->borderActiveColor : element->borderColor);

    DrawLineEx((Vector2) { (element->rect.x + element->rect.height), element->rect.y }, (Vector2) { (element->rect.x + element->rect.height), element->rect.y }, 1, element->borderColor);

  //  DrawTextEx(*(element->font), element->options[element->currentOption], element->textPosition, (float)element->fontSize, (float)element->spaceing, element->fontColor);
}

void InternalUpdateSlideBox(struct slideBox *element) {
    if (IsKeyPressed(KEY_LEFT)) {
        if (element->currentOption == 0) {
            element->currentOption = element->numberOfOptions - 1;
        } 
        else {
            element->currentOption -= 1;
        }
    }

    if (IsKeyPressed(KEY_RIGHT)) {
        element->currentOption += 1;
        element->currentOption %= element->numberOfOptions;
    }
}