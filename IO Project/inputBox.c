#include "inputBox.h"

#define MAX_INPUT_CHARS 30

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

void internalUpdateInputBox(struct inputBox *element) {
    // Get char pressed
    int key = GetCharPressed();

    // Check if more characters have been pressed on the same frame
    while (key > 0) {
        if ((key >= 32) && (key <= 125) && (element->currentLength < MAX_INPUT_CHARS)) {
            element->boxRectangle.width -= MeasureTextEx(*(element->font), element->text, (float)element->fontSize, (float)element->spaceing).x;

            element->text[element->currentLength] = (char)key;
            element->text[element->currentLength + 1] = '\0'; // Add null terminator at the end of the string.
            element->currentLength++;

            element->boxRectangle.width += MeasureTextEx(*(element->font), element->text, (float)element->fontSize, (float)element->spaceing).x;
        }

        key = GetCharPressed();  // Check next character in the queue
    }

    if (IsKeyPressed(KEY_BACKSPACE)) {
        element->boxRectangle.width -= MeasureTextEx(*(element->font), element->text, (float)element->fontSize, (float)element->spaceing).x;

        element->currentLength--;
        if (element->currentLength < 0) element->currentLength = 0;
        element->text[element->currentLength] = '\0';

        element->boxRectangle.width += MeasureTextEx(*(element->font), element->text, (float)element->fontSize, (float)element->spaceing).x;
    }
}