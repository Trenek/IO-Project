#include <string.h>

#include "state.h"

#include "menuElements.h"

#include "tutorialSlide.h"



void CalculateTutorialSlidePosition(struct tutorialSlide* this, Image tutorialImage) {
    struct slidePositionParameters init = this->init;
    this->initposX = init.posX;
    this-> initx = init.x;
    this->tutorialImageHeight = tutorialImage.height;
    this->tutorialImageWidth = tutorialImage.width;


    //uzupe?ni? 2. argument jako wczytany tekst z title i description
    //float size[2] = {
    // MeasureTextEx(*this->font, "_itoa(this->dataQuantity, buffor, 10)", (float)this->fontSize, (float)this->spaceing).x + (init.incX << 1),
    // MeasureTextEx(*this->font, "_itoa(this->dataQuantity, buffor, 10)", (float)this->fontSize, (float)this->spaceing).x + (init.incX << 1)
    //};

    this->height = this->fontSize + 2.0f * init.incY;
    this->top = init.y - (this->height * init.posY) / 2;


    this->titleBox = (struct textBox){
            .rec = {
                .x = (init.x - init.posX) / 2.0f,
                .y = (this->top + this->height)/10,
                .width = (float)init.width,
                .height = this->height
            },
            .textLeftCorner = (Vector2) {
                .x = (init.x - init.posX) / 2.0f + 5,
                .y = (this->top + this->height) / 10 + 5,
            }
    };

    this->descriptionBox = (struct textBox){
            .rec = {
                .x = (init.x - init.posX) / 2.0f,
                .y = (this->top + this->height) / 10 + this->height + this->tutorialImageHeight * init.x/this->tutorialImageWidth,
                .width = (float)init.width,
                .height = this->height*2
            },
            .textLeftCorner = (Vector2) {
                .x = (init.x - init.posX) / 2.0f + 5,
                .y = (this->top + this->height) / 10 + this->height + this->tutorialImageHeight * init.x / this->tutorialImageWidth + 5,
            }
    };

}

static void initializeButtons(struct tutorialSlide* this) {
    this->prev = (struct button){
        .text = "Poprzednie",
        .isActive = 1,
        .init = {
            .x = (int)this->descriptionBox.rec.x,
            .y = (int)(this->descriptionBox.rec.y + this->descriptionBox.rec.height),
            .incX = 10,
            .incY = 10,
            .posX = 0,
            .posY = 0
        },
        .font = this->font,
        .fontSize = this->fontSize,
        .fontColor = this->fontColor,
        .color = this->color,
        .hoverColor = this->hoverColor,
        .spaceing = this->spaceing
    };

    this->next = (struct button){
        .text = "Nastepne",
        .isActive = 1,
        .init = {
            .x = (int)(this->descriptionBox.rec.x + this->descriptionBox.rec.width),
            .y = (int)(this->descriptionBox.rec.y + this->descriptionBox.rec.height),
            .incX = 10,
            .incY = 10,
            .posX = 2,
            .posY = 0
        },
        .font = this->font,
        .fontSize = this->fontSize,
        .fontColor = this->fontColor,
        .color = this->color,
        .hoverColor = this->hoverColor,
        .spaceing = this->spaceing
    };

    CalculateButtonPosition(&this->prev);
    CalculateButtonPosition(&this->next);
}

void initializeTutorialSlideBox(struct tutorialSlide* this, Image tutorialImage) {
    CalculateTutorialSlidePosition(this, tutorialImage);
    initializeButtons(this);

    this->page = 0;

    this->prev.isActive = (this->page == 0) ? 0 : 1;
    this->next.isActive = ((this->page + 1) >= this->numOfSlides) ? 0 : 1;
}

void DrawTutorialSlideBox(struct tutorialSlide* this, Texture2D imageAsTexture) {
    Vector2 texturePosition;
    texturePosition.x = (this->initx - this->initposX) / 2.0f;
    texturePosition.y = (this->top + this->height) / 10.0f + this->height;


    DrawRectangleRec(this->titleBox.rec, this->color);

    DrawRectangleLinesEx(this->titleBox.rec, (float)this->width, this->borderColor);

    DrawRectangleRec(this->descriptionBox.rec, this->backgroundColor);

    DrawRectangleLinesEx(this->descriptionBox.rec, (float)this->width, this->borderColor);

    //uzupe?ni? 2. argument jako wczytany tekst z title i description
    DrawTextEx(*this->font, "title", this->titleBox.textLeftCorner, (float)this->fontSize, (float)this->spaceing, this->fontColor);
    DrawTextEx(*this->font, "description", this->descriptionBox.textLeftCorner, (float)this->fontSize, (float)this->spaceing, this->fontColor);
    DrawTextureEx(imageAsTexture, texturePosition, 0, (float)this->initx/800, WHITE);

    DrawButton(this->next);
    DrawButton(this->prev);

}

void UpdateTutorialSlideBox(struct tutorialSlide* this) {
    if (isMouseOver(this->prev)) this->page -= 1;
    else if (isMouseOver(this->next)) this->page += 1;

    this->prev.isActive = (this->page == 0) ? 0 : 1;
    this->next.isActive = ((this->page + 1) >= this->numOfSlides) ? 0 : 1;

}
