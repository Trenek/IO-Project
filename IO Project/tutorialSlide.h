#ifndef TUTORIAL_SLIDE_H
#define TUTORIAL_SLIDE_H

#include <raylib.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>



struct slidePositionParameters {
    int x;
    int y;
    int width;
    int incX;
    int incY;
    int posX;
    int posY;
};

struct textBox {
    Rectangle rec;
    Vector2 textLeftCorner;
};
struct tutorialSlide {
    int numOfSlides;
    int width;

    float height;
    float top;

    int initx;
    int initposX;

    struct button prev;
    struct button next;
    struct textBox titleBox;
    struct textBox descriptionBox;
    union {
        struct slidePositionParameters init;
        struct {
            FilePathList imgsList;

        };


        int page;


    };

    Font* font;
    int fontSize;
    Color fontColor;

    Color color;
    Color backgroundColor;
    Color titleDescriptionColor;
    Color borderColor;
    Color hoverColor;

    int spaceing;
};

void CalculateTutorialSlidePosition(struct tutorialSlide* this);
void initializeTutorialSlideBox(struct tutorialSlide* this);
void DrawTutorialSlideBox(struct tutorialSlide* this, Texture2D imageAsTexture);
void UpdateTutorialSlideBox(struct tutorialSlide* this);


#endif
