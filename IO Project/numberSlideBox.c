#ifndef NUMBER_SLIDEBOX_H
#define NUMBER_SLIDEBOX_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "numberSlideBox.h"

void nCalculateSlideBoxPosition(struct nSlideBox *element) {
    struct nSlideBoxPositionParameters init = element->init;

    element->rect[0] = (Rectangle){
        .x = init.x - init.posX * init.width / 2.0f,
        .y = init.y - init.posY * (element->fontSize + 2.0f * init.incY) / 2,
        .width = (float)init.width + init.incX * 2.0f,
        .height = element->fontSize + init.incY * 2.0f
    };

    element->rect[1] = (Rectangle){
        .x = element->rect[0].x,
        .y = element->rect[0].y,
        .width = element->rect[0].height,
        .height = element->rect[0].height
    };

    element->rect[2] = (Rectangle){
        .x = element->rect[0].x + element->rect[0].width - element->rect[0].height,
        .y = element->rect[0].y,
        .width = element->rect[0].height,
        .height = element->rect[0].height
    };

    element->incY = (float)init.incY;
}

void nDrawSlideBox(const struct nSlideBox *element) {
    char buffer[8];
    const float textWidth = MeasureTextEx(*element->font, itoa(element->currentOption + 1, buffer, 10), (float)element->fontSize, (float)element->spaceing).x;
    const Vector2 vec = {
        .x = element->rect[0].x + (element->rect[0].width - textWidth) / 2,
        .y = element->rect[0].y + element->incY
    };

    DrawRectangleRec(element->rect[0], element->color);

    DrawRectangleLinesEx(element->rect[0], 1, element->isActive ? element->borderActiveColor : element->borderColor);
    DrawRectangleLinesEx(element->rect[1], 1, element->isActive ? element->borderActiveColor : element->borderColor);
    DrawRectangleLinesEx(element->rect[2], 1, element->isActive ? element->borderActiveColor : element->borderColor);

    DrawTextEx(*(element->font), buffer, vec, (float)element->fontSize, (float)element->spaceing, element->fontColor);
}

void nInternalUpdateSlideBox(struct nSlideBox *element) {
    if (IsKeyPressed(KEY_LEFT) || (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), element->rect[1]))) {
        if (element->currentOption == 0) {
            element->currentOption = element->numberOfOptions - 1;
        }
        else {
            element->currentOption -= 1;
        }
    }

    if (IsKeyPressed(KEY_RIGHT) || (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), element->rect[2]))) {
        if (element->currentOption == element->numberOfOptions) {
            element->currentOption = 0;
        }
        else {
            element->currentOption += 1;
            element->currentOption %= element->numberOfOptions;
        }
    }
}

#endif