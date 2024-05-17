#include "tutorialSlide.h"

void CalculateSlidePosition(struct tutorialSlide* element) {

    element->BackgroundLeftCorner = (Vector2){
        .x = 125,
        .y = 50
    };

    element->TitleTextBoxLeftCorner = (Vector2){
        .x = element->BackgroundLeftCorner.x + 5,
        .y = element->BackgroundLeftCorner.y + 5
    };

    element->TitleTextBoxLeftCorner = (Vector2){
        .x = 125,
        .y = 50
    };

    element->backgroundBoxRectangle = (Rectangle){
        .x = element->BackgroundLeftCorner.x,
        .y = element->BackgroundLeftCorner.y,
        .width = 550,
        .height = 500
    };

    element->titleBoxRectangle = (Rectangle){
        .x = element->TitleTextBoxLeftCorner.x + 24,
        .y = element->TitleTextBoxLeftCorner.y + 20,
        .width = 500,
        .height = 100
    };

    element->descriptionBoxRectangle = (Rectangle){
        .x = element->TitleTextBoxLeftCorner.x + 24,
        .y = element->TitleTextBoxLeftCorner.y + 200,
        .width = 500,
        .height = 100
    };
}

void DrawSlide(struct tutorialSlide element) {
    DrawRectangleRec(element.backgroundBoxRectangle, element.backgroundColor);
    DrawRectangleRec(element.titleBoxRectangle, element.titleDescriptionColor);
    DrawRectangleRec(element.descriptionBoxRectangle, element.titleDescriptionColor);
    DrawTextEx(*element.font, element.text, element.BackgroundLeftCorner, (float)element.fontSize, (float)element.spaceing, element.fontColor);
}