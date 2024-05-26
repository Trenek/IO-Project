#ifndef ITEMBOX_H
#define ITEMBOX_H

#include <raylib.h>

struct playInfo;
struct itemBoxPositionParameters {
    int x;
    int y;
    int posX;
    int posY;
    int width;
    int height;
};

struct itemBox {
    bool isActive;

    union {
        struct itemBoxPositionParameters init;
        Rectangle boxRectangle;
    };

    Color color;
    Color activeColor;
    Color borderColor;
};

void CalculateItemBoxPosition(struct itemBox* element);
void DrawItemBox(const struct itemBox element);
void DrawItem(int b, int a, int c, Rectangle itemBox, const struct playInfo *info);

inline bool isMouseOverItemBox(struct itemBox element) {
    return CheckCollisionPointRec(GetMousePosition(), element.boxRectangle);
}
#endif