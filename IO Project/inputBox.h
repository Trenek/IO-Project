#pragma once
#ifndef INPUTBOX
#define INPUTBOX

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
int updateInputBox(struct inputBox* input);

#endif // !INPUTBOX