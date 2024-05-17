#include <string.h>

#include "choiceBox.h"

void CalculateChoiceBoxPosition(struct choiceBox* element) {
    struct choiceBoxPositionParameters init = element->init;

    element->LeftCorner = (Vector2){
         .x = init.x - 322.5f,
         .y = init.y  + 70.0f
    };

    for (int i = 0; i < 6; i++) {
        element->mainBoxRectangle[i] = (Rectangle){
            .x = element->LeftCorner.x,
            .y = element->LeftCorner.y + 50.0f * i,
            .width = 650.0f,
            .height = 50.0f
        };

        element->numBoxRectangle[i] = (Rectangle){
            .x = element->LeftCorner.x + 5,
            .y = element->LeftCorner.y + 50.0f * i + 5,
            .width = 40.0f,
            .height = 40.0f
        };

        element->nameBoxRectangle[i] = (Rectangle){
            .x = element->LeftCorner.x + 50,
            .y = element->LeftCorner.y + 50.0f * i + 5,
            .width = 450.0f,
            .height = 40.0f
           
        };

        element->dateBoxRectangle[i] = (Rectangle){
            .x = element->LeftCorner.x + 505,
            .y = element->LeftCorner.y + 50.0f * i + 5,
            .width = 140,
            .height = 40
        };
    }

}

void DrawChoiceBox(struct choiceBox element) {
    
    for (int i = 0; i < 6; i++) {
        DrawRectangleRec(element.mainBoxRectangle[i], CheckCollisionPointRec(GetMousePosition(), element.mainBoxRectangle[i]) ? element.hoverColor : element.color);
        DrawRectangleLinesEx(element.mainBoxRectangle[i], 1, element.isActive ? element.borderActiveColor : element.borderColor);
        DrawTextEx(*(element.font), element.text, element.LeftCorner, (float)element.fontSize, (float)element.spaceing, element.fontColor);

        DrawRectangleRec(element.numBoxRectangle[i], element.color );
        DrawRectangleLinesEx(element.numBoxRectangle[i], 1, element.isActive ? element.borderActiveColor : element.borderColor);
        DrawTextEx(*(element.font), element.text, element.LeftCorner, (float)element.fontSize, (float)element.spaceing, element.fontColor);

        DrawRectangleRec(element.nameBoxRectangle[i], element.color);
        DrawRectangleLinesEx(element.nameBoxRectangle[i], 1, element.isActive ? element.borderActiveColor : element.borderColor);
        DrawTextEx(*(element.font), element.text, element.LeftCorner, (float)element.fontSize, (float)element.spaceing, element.fontColor);

        DrawRectangleRec(element.dateBoxRectangle[i], element.color);
        DrawRectangleLinesEx(element.dateBoxRectangle[i], 1, element.isActive ? element.borderActiveColor : element.borderColor);
        DrawTextEx(*(element.font), element.text, element.LeftCorner, (float)element.fontSize, (float)element.spaceing, element.fontColor);
    };
}


