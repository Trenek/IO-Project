#ifndef INPUTBOX_H
#define INPUTBOX_H

#include <raylib.h>

struct inputBox {
    char text[128];
    int currentLength;
    bool isActive;

    int x;
    int y;
    int width;
    int incX;
    int incY;
    Font *font;
    int fontSize;
    Color fontColor;
    Color color;
    Color borderActiveColor;
    Color borderColor;
    int spaceing;
};

void DrawInputBox(struct inputBox* input);
void internalUpdateInputBox(struct inputBox *input);

inline void UpdateInputBox(struct inputBox *input) {
    if (input->isActive) internalUpdateInputBox(input);
}



#endif // !INPUTBOX