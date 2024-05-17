#pragma once
#ifndef MENU_ELEMENT_H
#define MENU_ELEMENT_H

#include <raylib.h>

#include "state.h"

struct slidePositionParameters {
    int x;
    int y;
    int incX;
    int incY;
    int posX; // 0 - left, 1 - center, 2 - right
    int posY; // 0 - up, 1 - center, 2 - bottom
};

struct slide {
    const char* text;
    union {
        struct slidePositionParameters init;
        struct {
            Vector2 textLeftCorner;
            Rectangle boxRectangle;
        };
    };
    Font* font;
    int fontSize;
    Color fontColor;
    Color color;
    Color hoverColor;
    int spaceing;
};

void CalculateSlidePosition(struct slide* element);
void DrawSlide(struct slide element);



#endif