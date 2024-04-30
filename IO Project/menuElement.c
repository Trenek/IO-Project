#include "menuElement.h"

void DrawMenuElement(struct menuElement element) {
    Vector2 size = MeasureTextEx(*element.font, element.text, (float)element.fontSize, (float)element.spaceing);
    Rectangle rec = { element.x - (size.x / 2) - element.incX, element.y - (size.y / 2) - element.incY, size.x + (element.incX << 1), size.y + (element.incY << 1) };

    DrawRectangleRec(rec, CheckCollisionPointRec(GetMousePosition(), rec) ? element.hoverColor : element.color);
    DrawTextEx(*element.font, element.text, (Vector2) {.x = (float)element.x - size.x / 2.0f, .y = (float)element.y - size.y / 2.0f }, (float)element.fontSize, (float)element.spaceing, element.fontColor);
}