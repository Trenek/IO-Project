#include <raylib.h>

#include "state.h"

#ifndef MENU_ELEMENT_H
#define MENU_ELEMENT_H

struct buttonPositionParameters {
    int x;
    int y;
    int incX;
    int incY;
    int posX;
    int posY;
};

struct button {
    const char *text;
    union {
        struct buttonPositionParameters init;
        struct {
            Vector2 textLeftCorner;
            Rectangle boxRectangle;
        };
    };
    Font *font;
    int fontSize;
    Color fontColor;
    Color color;
    Color hoverColor;
    int spaceing;
};

inline void CalculateButtonPosition(struct button *element) {
    Vector2 size = MeasureTextEx(*element->font, element->text, (float)element->fontSize, (float)element->spaceing);
    struct buttonPositionParameters initial = element->init;

    element->textLeftCorner = (Vector2) {
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

inline bool isMouseOver(struct button element) {
    return CheckCollisionPointRec(GetMousePosition(), element.boxRectangle);
}

#endif

void DrawButton(struct button element);