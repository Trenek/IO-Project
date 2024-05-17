#ifndef SELECTIONBOX_H
#define SELECTIONBOX_H

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

struct slideBox {
    int numberOfOptions;
    bool isActive;
    int currentOption;
    char **options;

    union {
        struct slideBoxPositionParameters init;
        struct {
            Rectangle boxRectangle;
            Rectangle boxLeftRectangle;
            Rectangle boxRightRectangle;
        };
    };

    Font *font;
    int fontSize;
    Color fontColor;
    Color color;
    Color borderActiveColor;
    Color borderColor;
    int spaceing;
};

void CalculateSelectionBoxPosition(struct slideBox *element);
void DrawSelectionBox(struct slideBox *element);
void InternalUpdateSelectionBox(struct slideBox *element);

inline void UpdateSelectionBox(struct slideBox *element) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        element->isActive = CheckCollisionPointRec(GetMousePosition(), element->boxRectangle);
        if (CheckCollisionPointRec(GetMousePosition(), element->boxLeftRectangle)) {
            element->isActive = true;
            if (element->currentOption == 0) {
                element->currentOption = element->numberOfOptions - 1;
            }
            else {
                element->currentOption -= 1;
            }
        }
        else if (CheckCollisionPointRec(GetMousePosition(), element->boxRightRectangle)) {
            element->isActive = true;
            element->currentOption += 1;
            element->currentOption %= element->numberOfOptions;
        }
    }

    if (element->isActive) InternalUpdateSelectionBox(element);
}

#endif