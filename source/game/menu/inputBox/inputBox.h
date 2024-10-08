#ifndef INPUTBOX_H
#define INPUTBOX_H

#include <raylib.h>

struct inputBoxPositionParameters {
    int x;
    int y;
    int incX;
    int incY;
    int posX;
    int posY;
    int width;
};

struct inputBox {
    char text[128];
    int length[128];

    int currentLength;
    int lengthArrayLength;

    bool isActive;

    int textOffset;

    union {
        struct inputBoxPositionParameters init;
        struct {
            Vector2 textLeftCorner;
            Rectangle boxRectangle;
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

void CalculateInputBoxPosition(struct inputBox *element);
void DrawInputBox(const struct inputBox *element);
void InternalUpdateInputBox(struct inputBox *element);

inline void UpdateInputBox(struct inputBox *input) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        input->isActive = CheckCollisionPointRec(GetMousePosition(), input->boxRectangle);
    }

    if (input->isActive) InternalUpdateInputBox(input);
}

#endif