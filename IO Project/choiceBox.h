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

enum choiceBoxColumn {
    MAIN,
    NUM,
    NAME,
    DATE
};

struct choiceBox {
    char text[128];
    char* saveNames[128];
    int currentLength;
    bool isActive;

    unsigned int clicked;

    union {
        struct choiceBoxPositionParameters init;
        struct {
            Vector2 LeftCorner[4];
            Rectangle rowRectangle[4][6];
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
void DrawChoiceBox(struct choiceBox element, unsigned int *clicked);

#endif