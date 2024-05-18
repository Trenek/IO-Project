#ifndef SLIDEBOX_H
#define SLIDEBOX_H

#include <raylib.h>

struct slideBoxPositionParameters {
    int x;
    int y;
    int incX;
    int incY;
    int posX;
    int posY;
    int width;
};

enum slideBoxRect {
    SB_LEFT,
    SB_MIDDLE,
    SB_RIGHT
};

struct slideBox {
    int numberOfOptions;
    bool isActive;
    int currentOption;

    union {
        struct slideBoxPositionParameters init;
        struct {
            Rectangle rect[3];
            Vector2 textPosition;
        };
    };

    Font *font;
    int fontSize;
    Color fontColor;
    Color color;
    Color borderActiveColor;
    Color borderColor;
    int spaceing;
    char * const options[];
};

void CalculateSlideBoxPosition(struct slideBox *element);
void DrawSlideBox(struct slideBox *element);
void InternalUpdateSlideBox(struct slideBox *element);

inline void UpdateSlideBox(struct slideBox *element) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        element->isActive = CheckCollisionPointRec(GetMousePosition(), element->rect[SB_MIDDLE]);
        if (CheckCollisionPointRec(GetMousePosition(), element->rect[SB_LEFT])) {
            element->isActive = true;

            element->currentOption = (element->currentOption == 0 ? element->numberOfOptions : element->currentOption) - 1;
        }
        else if (CheckCollisionPointRec(GetMousePosition(), element->rect[SB_RIGHT])) {
            element->isActive = true;

            element->currentOption += 1;
            element->currentOption %= element->numberOfOptions;
        }
    }

    if (element->isActive) InternalUpdateSlideBox(element);
}

#endif