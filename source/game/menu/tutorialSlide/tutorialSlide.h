#ifndef TUTORIAL_SLIDE_H
#define TUTORIAL_SLIDE_H

#include <raylib.h>

struct slidePositionParameters {
    int x;
    int y;
    int height;
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
    int lineWidth;

    union {
        struct slidePositionParameters init;
        struct {
            int numOfSlides;

            struct button prev;
            struct button next;
            struct textBox titleBox;
            struct textBox descriptionBox;

            Texture2D image;
            char *description;
            char *title;

            Vector2 texturePosition;

            int page;
        };
    };

    Font *font;
    int fontSize;
    Color fontColor;

    Color color;
    Color backgroundColor;
    Color titleDescriptionColor;
    Color borderColor;
    Color hoverColor;

    int spaceing;
};

void initializeTutorialSlideBox(struct tutorialSlide *this);
void freeTutorialSlideBox(struct tutorialSlide *this);

void DrawTutorialSlideBox(struct tutorialSlide *this);
void UpdateTutorialSlideBox(struct tutorialSlide *this);

#endif
