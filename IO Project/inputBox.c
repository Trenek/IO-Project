#include <string.h>

#include "inputBox.h"

#define MAX_INPUT_CHARS 30
#define BACKSPACE 20

void CalculateInputBoxPosition(struct inputBox *element) {
    Vector2 size = MeasureTextEx(*(element->font), element->text, (float)element->fontSize, (float)element->spaceing);
    struct inputBoxPositionParameters init = element->init;

    element->textLeftCorner = (Vector2){
         .x = init.x - init.posX * size.x / 2.0f,
         .y = init.y - init.posY * size.y / 2.0f
    };

    element->boxRectangle = (Rectangle){
        .x = element->textLeftCorner.x - init.incX,
        .y = element->textLeftCorner.y - init.incY,
        .width = size.x + (init.incX << 1),
        .height = size.y + (init.incY << 1)
    };
}

void DrawInputBox(struct inputBox *element) {
    DrawRectangleRec(element->boxRectangle, element->color);
    DrawRectangleLinesEx(element->boxRectangle, 1, element->isActive ? element->borderActiveColor : element->borderColor);
    DrawTextEx(*(element->font), element->text, element->textLeftCorner, (float)element->fontSize, (float)element->spaceing, element->fontColor);
}

void InternalUpdateInputBox(struct inputBox *element) {
    static int backspace = 0;
    static int interval = 0;
    int key = GetCharPressed();
    int size = 0;

    while (key > 0) {
        if (element->currentLength < MAX_INPUT_CHARS) {
            element->boxRectangle.width -= MeasureTextEx(*(element->font), element->text, (float)element->fontSize, (float)element->spaceing).x;
            element->text[element->currentLength] = '\0';

            strcat(element->text, CodepointToUTF8(key, &size));
            element->currentLength += size;

            element->text[element->currentLength] = '\0';
            element->boxRectangle.width += MeasureTextEx(*(element->font), element->text, (float)element->fontSize, (float)element->spaceing).x;
        }

        key = GetCharPressed();
    }

    if ((backspace < BACKSPACE ? IsKeyPressed : IsKeyDown)(KEY_BACKSPACE)) {
        element->boxRectangle.width -= MeasureTextEx(*(element->font), element->text, (float)element->fontSize, (float)element->spaceing).x;

        if (interval == 0) {
            if (element->currentLength > 0) {
                element->currentLength -= 1; // TODO: Delete whole character by single click
            }
        }

        element->text[element->currentLength] = '\0';

        element->boxRectangle.width += MeasureTextEx(*(element->font), element->text, (float)element->fontSize, (float)element->spaceing).x;
    }

    // TODO: connect this to GetFrameTime
    if (IsKeyDown(KEY_BACKSPACE)) {
        backspace += 1;
        interval += 1;
    }
    else {
        backspace = 0;
        interval = 0;
    }

    interval %= 2;
}