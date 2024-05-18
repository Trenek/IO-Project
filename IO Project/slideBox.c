#include <string.h>

#include "slideBox.h"

void CalculateSlideBoxPosition(struct slideBox *element) {
    Vector2 size = MeasureTextEx(*(element->font), element->options[element->currentOption], (float)element->fontSize, (float)element->spaceing);
    struct slideBoxPositionParameters init = element->init;

    element->rect[SB_MIDDLE] = (Rectangle){
        .x = init.x - init.width / 2.0f,
        .y = init.y - init.posY * size.y / 2.0f - init.incY,
        .width = (float)init.width + (init.incX << 1),
        .height = size.y + (init.incY << 1)
    };
    element->rect[SB_LEFT] = (Rectangle){
        .x = element->rect[SB_MIDDLE].x - 40,
        .y = element->rect[SB_MIDDLE].y,
        .width = 40,
        .height = element->rect[SB_MIDDLE].height
    };
    element->rect[SB_RIGHT] = (Rectangle){
        .x = element->rect[SB_MIDDLE].x + element->rect[SB_MIDDLE].width,
        .y = element->rect[SB_MIDDLE].y,
        .width = 40,
        .height = element->rect[SB_MIDDLE].height
    };

    element->textPosition = (Vector2){
        .x = element->rect[SB_MIDDLE].x + element->rect[SB_MIDDLE].width / 2 - size.x / 2,
        .y = element->rect[SB_MIDDLE].y
    };
}

void DrawSlideBox(struct slideBox *element) {
    int i = 0;

    while (i < 3) {
        DrawRectangleRec(element->rect[i], element->color);
        DrawRectangleLinesEx(element->rect[i], 1, element->isActive ? element->borderActiveColor : element->borderColor);

        i += 1;
    }

    DrawTextEx(*(element->font), element->options[element->currentOption], element->textPosition, (float)element->fontSize, (float)element->spaceing, element->fontColor);
}

void InternalUpdateSlideBox(struct slideBox *element) {
    if (IsKeyPressed(KEY_LEFT)) {
        if (element->currentOption == 0) {
            element->currentOption = element->numberOfOptions - 1;
        } 
        else {
            element->currentOption -= 1;
        }
    }

    if (IsKeyPressed(KEY_RIGHT)) {
        element->currentOption += 1;
        element->currentOption %= element->numberOfOptions;
    }
}