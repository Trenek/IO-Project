#ifndef ITEMBOX_H
#define ITEMBOX_H

#include <raylib.h>

struct itemBoxPositionParameters {
    int x;
    int y;
    int incX;
    int incY;
    int width;
    int height;
};

struct itemBox {
    bool isActive;

    union {
        struct itemBoxPositionParameters init;
        Rectangle boxRectangle;
    };

    Texture2D item;
    Color color;
    Color activeColor;
    Color borderColor;
    int spaceing;
};

void CalculateItemBoxPosition(struct itemBox* element);
void DrawItemBox(struct itemBox element);

inline bool isMouseOverItemBox(struct itemBox element) {
    return CheckCollisionPointRec(GetMousePosition(), element.boxRectangle);
}
#endif