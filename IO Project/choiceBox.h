#ifndef CHOICEBOX_H
#define CHOICEBOX_H

#include <raylib.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct saveData;
struct menuInfo;

struct choiceBoxPositionParameters {
    int x;
    int y;
    int width;
    int incX;
    int incY;
    int posX;
    int posY;
};

struct cell {
    Rectangle rec;
    Vector2 textLeftCorner;
};

enum choiceBoxColumn {
    NUM,
    NAME,
    DATE,
    MAIN
};

struct choiceBox {
    int rowQuantity;
    int wideness;


    struct button prev;
    struct button next;

    union {
        struct choiceBoxPositionParameters init;
        struct {
            struct saveData *saveData;
            int dataQuantity;

            int chosenRow;
            int page;

            struct cell (*row)[4];

            Rectangle prevRec;
            Rectangle nextRec;
        };
    };

    Font* font;
    Color fontColor;
    int fontSize;
    int spaceing;

    Color color;
    Color activeBorderColor;
    Color inactiveBorderColor;
    Color hoverColor;
};

void initializeChoiceBox(struct choiceBox *const this);
void freeChoiceBox(struct choiceBox *const this);

void DrawChoiceBox(struct choiceBox *const this);
void UpdateChoiceBox(struct choiceBox *const this, struct menuInfo *info);

#endif