#include "button.h"

void CalculateButtonPosition(struct button *element) {
    Vector2 size = MeasureTextEx(*element->font, element->text, (float)element->fontSize, (float)element->spaceing);
    struct buttonPositionParameters initial = element->init;

    element->textLeftCorner = (Vector2){
        .x = initial.x - initial.posX * size.x / 2,
        .y = initial.y - initial.posY * size.y / 2
    };

    element->boxRectangle = (Rectangle){
        .x = element->textLeftCorner.x - initial.incX,
        .y = element->textLeftCorner.y - initial.incY,
        .width = size.x + 2 * initial.incX,
        .height = size.y + 2 * initial.incY
    };
}

void DrawButton(struct button element) {
    DrawRectangleRec(element.boxRectangle, CheckCollisionPointRec(GetMousePosition(), element.boxRectangle) ? element.hoverColor : element.color);
    DrawTextEx(*element.font, element.text, element.textLeftCorner, (float)element.fontSize, (float)element.spaceing, element.fontColor);
}