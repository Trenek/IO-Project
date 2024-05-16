#include "button.h"

void DrawButton(struct button element) {
    DrawRectangleRec(element.boxRectangle, CheckCollisionPointRec(GetMousePosition(), element.boxRectangle) ? element.hoverColor : element.color);
    DrawTextEx(*element.font, element.text, element.textLeftCorner, (float)element.fontSize, (float)element.spaceing, element.fontColor);
}