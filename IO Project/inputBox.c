#include <string.h>

#include "inputBox.h"

#define MAX_INPUT_CHARS 120
#define BLINK_INTERVAL 25
#define BACKSPACE 20

void CalculateInputBoxPosition(struct inputBox *element) {
    Vector2 size = MeasureTextEx(*(element->font), element->text, (float)element->fontSize, (float)element->spaceing);
    struct inputBoxPositionParameters init = element->init;

    element->lengthArrayLength = 0;
    element->currentLength = 0;

    element->textLeftCorner = (Vector2){
         .x = init.x - init.posX * size.x / 2.0f,
         .y = init.y - init.posY * size.y / 2.0f
    };

    element->boxRectangle = (Rectangle){
        .x = element->textLeftCorner.x - init.incX,
        .y = element->textLeftCorner.y - init.incY,
        .width = (float)init.width + (init.incX << 1),
        .height = size.y + (init.incY << 1)
    };

    element->textOffset = 0;
    while (MeasureTextEx(*element->font, element->text + element->textOffset, (float)element->fontSize, (float)element->spaceing).x + 2 * init.incX > element->boxRectangle.width) {
        element->textOffset += 1;
    }
}

void DrawInputBox(struct inputBox *element) {
    static int framesCounter = 0;

    float width = 0;

    DrawRectangleRec(element->boxRectangle, element->color);
    DrawRectangleLinesEx(element->boxRectangle, 1, element->isActive ? element->borderActiveColor : element->borderColor);
    DrawTextEx(*(element->font), element->text + element->textOffset, element->textLeftCorner, (float)element->fontSize, (float)element->spaceing, element->fontColor);

    if (element->isActive) {
        if (((framesCounter / BLINK_INTERVAL) % 2) == 0) {
            width = MeasureTextEx(*element->font, element->text + element->textOffset, (float)element->fontSize, (float)element->spaceing).x;

            DrawTextEx(*element->font, "_", (Vector2) { element->textLeftCorner.x + width, element->textLeftCorner.y }, (float)element->fontSize, (float)element->spaceing, element->fontColor);
        }

        framesCounter += 1;
    }

}

void InternalUpdateInputBox(struct inputBox *element) {
    static float backspace = 0.0f;
    static int interval = 0;
    int key = GetCharPressed();
    int size = 0;
    float incX = element->textLeftCorner.x - element->boxRectangle.x;

    while (key > 0) {
        if (element->currentLength < MAX_INPUT_CHARS) {
            element->text[element->currentLength] = '\0';

            strcat(element->text, CodepointToUTF8(key, &size));
            element->currentLength += size;

            element->length[element->lengthArrayLength] = size;
            element->lengthArrayLength += 1;

            element->text[element->currentLength] = '\0';
        }

        while (MeasureTextEx(*element->font, element->text + element->textOffset, (float)element->fontSize, (float)element->spaceing).x + 2 * incX > element->boxRectangle.width) {
            element->textOffset += 1;
        }

        key = GetCharPressed();
    }

    if ((backspace < BACKSPACE ? IsKeyPressed : IsKeyDown)(KEY_BACKSPACE)) {
        if (interval == 0) {
            if (element->currentLength > 0) {
                element->currentLength -= element->length[element->lengthArrayLength - 1];
                element->lengthArrayLength -= 1;
            }
        }

        element->text[element->currentLength] = '\0';

        element->textOffset = 0;
        while (MeasureTextEx(*element->font, element->text + element->textOffset, (float)element->fontSize, (float)element->spaceing).x + 2 * incX > element->boxRectangle.width) {
            element->textOffset += 1;
        }
    }

    if (IsKeyDown(KEY_BACKSPACE)) {
        backspace += GetFrameTime() * 60;
        interval += 1;
    }
    else {
        backspace = 0;
        interval = 0;
    }

    interval %= 2;
}