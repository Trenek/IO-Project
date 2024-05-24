#include "button.h"

void CalculateButtonPosition(struct button *element) {

    Vector2 size = MeasureTextEx(*element->font, element->text, (float)element->fontSize, (float)element->spaceing);
    struct buttonPositionParameters initial = element->init;

    element->boxRectangle = (Rectangle){
        .x = initial.x - initial.posX * (initial.incX + size.x / 2.0f),
        .y = initial.y - initial.posY * (initial.incY + size.y / 2.0f),
        .width = size.x + 2 * initial.incX,
        .height = size.y + 2 * initial.incY
    };

    element->textLeftCorner = (Vector2){
        .x = element->boxRectangle.x + initial.incX,
        .y = element->boxRectangle.y + initial.incY
    };

    element->boxRectangle = (Rectangle){
        .x = element->textLeftCorner.x - initial.incX,
        .y = element->textLeftCorner.y - initial.incY,
        .width = size.x + 2 * initial.incX,
        .height = size.y + 2 * initial.incY
    };
}

void DrawButton(struct button element) {
    DrawRectangleRec(element.boxRectangle, !element.isActive || !CheckCollisionPointRec(GetMousePosition(), element.boxRectangle) ? element.color : element.hoverColor);
    DrawTextEx(*element.font, element.text, element.textLeftCorner, (float)element.fontSize, (float)element.spaceing, element.fontColor);

    if (!element.isActive) {
        DrawRectangleRec(element.boxRectangle, (Color) { .r = 100, .g = 100, .b = 100, .a = 100 });
    }
}