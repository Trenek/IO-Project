#ifndef BUTTON_H
#define BUTTON_H

#include <raylib.h>

#include "state.h"

struct buttonPositionParameters {
    int x;
    int y;
    int incX;
    int incY;
    int posX; // 0 - left, 1 - center, 2 - right
    int posY; // 0 - up, 1 - center, 2 - bottom
};

struct button {
    const char *text;

    bool isActive;

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
    int spaceing;

    Color color;
    Color hoverColor;
};

void CalculateButtonPosition(struct button *element);
void DrawButton(struct button element);

inline bool isMouseOver(struct button element) {
    return element.isActive && CheckCollisionPointRec(GetMousePosition(), element.boxRectangle);
}

#endif