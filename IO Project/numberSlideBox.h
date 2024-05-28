#define SLIDEBOX_H

#include <raylib.h>

struct nSlideBoxPositionParameters {
    int x;
    int y;
    int incX;
    int incY;
    int posX;
    int posY;
    int width;
};

struct nSlideBox {
    int numberOfOptions;
    bool isActive;
    int currentOption;

    union {
        struct nSlideBoxPositionParameters init;
        struct {
            Rectangle rect[3];
            float incY;
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

void nCalculateSlideBoxPosition(struct nSlideBox *element);
void nDrawSlideBox(const struct nSlideBox *element);
void nInternalUpdateSlideBox(struct nSlideBox *element);

inline void nUpdateSlideBox(struct nSlideBox *element) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        element->isActive = CheckCollisionPointRec(GetMousePosition(), element->rect[0]);
    }

    if (element->isActive) nInternalUpdateSlideBox(element);
}