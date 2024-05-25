#include "tutorialSlide.h"

void CalculateSlidePosition(struct tutorialSlide* element) {

    element->BackgroundLeftCorner = (Vector2){
        .x = 125,
        .y = 50
    };

    element->backgroundBoxRectangle = (Rectangle){
        .x = element->BackgroundLeftCorner.x,
        .y = element->BackgroundLeftCorner.y,
        .width = 550,
        .height = 500
    };

    element->ImageLeftCorner = (Vector2){
        .x = element->BackgroundLeftCorner.x,
        .y = element->BackgroundLeftCorner.y + 75
    };

    element->titleBoxRectangle = (Rectangle){
        .x = element->backgroundBoxRectangle.x,
        .y = element->backgroundBoxRectangle.y,
        .width = 492,
        .height = 100
    };

    element->descriptionBoxRectangle = (Rectangle){
        .x = element->backgroundBoxRectangle.x,
        .y = element->backgroundBoxRectangle.y + 380,
        .width = 492,
        .height = 130
    };

    element->TitleTextBoxLeftCorner = (Vector2){
        .x = element->titleBoxRectangle.x + 5,
        .y = element->titleBoxRectangle.y + 5
    };

    element->DescriptionTextBoxLeftCorner = (Vector2){
        .x = element->descriptionBoxRectangle.x + 5,
        .y = element->descriptionBoxRectangle.y + 5
    };
}

void DrawSlide(const struct tutorialSlide element, const char* title, const char* description, Texture2D imageAsTexture) {

    DrawRectangleRec(element.titleBoxRectangle, element.titleDescriptionColor);
    DrawRectangleRec(element.descriptionBoxRectangle, element.titleDescriptionColor);
    DrawTextEx(*element.font, title, element.TitleTextBoxLeftCorner, (float)element.fontSize, (float)element.spaceing, element.fontColor);
    DrawTextEx(*element.font, description, element.DescriptionTextBoxLeftCorner, (float)element.fontSize, (float)element.spaceing, element.fontColor);

    DrawTexture(imageAsTexture, (int) element.ImageLeftCorner.x, (int) element.ImageLeftCorner.y, WHITE);
}