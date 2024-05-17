#ifndef CHOICEBOX_H
#define CHOICEBOX_H

#include <raylib.h>

struct choiceBoxPositionParameters {
    int x;
    int y;
    int incX;
    int incY;
    int posX;
    int posY;
};

struct choiceBox {
    char text[128];
    int currentLength;
    bool isActive;

    union {
        struct choiceBoxPositionParameters init;
        struct {
            Vector2 LeftCorner;
            Rectangle mainBoxRectangle[6];
            Rectangle numBoxRectangle[6];
            Rectangle nameBoxRectangle[6];
            Rectangle dateBoxRectangle[6];
        };
    };

    Font* font;
    int fontSize;
    Color fontColor;
    Color color;
    Color borderActiveColor;
    Color borderColor;
    int spaceing;
    Color hoverColor;
};

void CalculateChoiceBoxPosition(struct choiceBox* element);
void DrawChoiceBox(struct choiceBox element);

#endif