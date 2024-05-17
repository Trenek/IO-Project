#ifndef TUTORIAL_SLIDE_H
#define TUTORIAL_SLIDE_H

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

struct tutorialSlide {
    const char* text;
    union {
        struct slidePositionParameters init;
        struct {
            Vector2 BackgroundLeftCorner;
            Vector2 TitleTextBoxLeftCorner;
            Vector2 DescriptionTextBoxLeftCorner;

            Rectangle backgroundBoxRectangle;
            Rectangle titleBoxRectangle;
            Rectangle descriptionBoxRectangle;

        };
    };
    Font* font;
    int fontSize;
    Color fontColor;
    Color backgroundColor;
    Color titleDescriptionColor;
    Color borderColor;
    int spaceing;
};

void CalculateSlidePosition(struct tutorialSlide* element);
void DrawSlide(struct tutorialSlide element);



#endif