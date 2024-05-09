#include <raylib.h>

#include "state.h"

#ifndef MENU_ELEMENT_H
#define MENU_ELEMENT_H

struct button {
    const char *text;
    int x;
    int y;
    int incX;
    int incY;
    Font *font;
    int fontSize;
    Color fontColor;
    Color color;
    Color hoverColor;
    int spaceing;
};

inline bool isMouseOver(struct button element) {
    Vector2 size = MeasureTextEx(*element.font, element.text, (float)element.fontSize, (float)element.spaceing);
    Rectangle rec = { element.x - (size.x / 2) - element.incX, element.y - (size.y / 2) - element.incY, size.x + (element.incX << 1), size.y + (element.incY << 1) };

    return CheckCollisionPointRec(GetMousePosition(), rec);
}

inline bool isMouseOverLeft(struct button element) {
    Vector2 size = MeasureTextEx(*element.font, element.text, (float)element.fontSize, (float)element.spaceing);
    Rectangle rec = { (float)element.x - element.incX, element.y - (size.y / 2) - element.incY, size.x + (element.incX << 1), size.y + (element.incY << 1) };

    return CheckCollisionPointRec(GetMousePosition(), rec);
}

inline bool isMouseOverRight(struct button element) {
    Vector2 size = MeasureTextEx(*element.font, element.text, (float)element.fontSize, (float)element.spaceing);
    Rectangle rec = { element.x - size.x- element.incX, element.y - (size.y / 2) - element.incY, size.x + (element.incX << 1), size.y + (element.incY << 1) };

    return CheckCollisionPointRec(GetMousePosition(), rec);
}

#endif

void DrawButton(struct button element);
void DrawButtonLeft(struct button element);
void DrawButtonRight(struct button element);