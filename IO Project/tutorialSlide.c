#include <string.h>

#include "state.h"

#include "menuElements.h"

#include "tutorialSlide.h"



void CalculateTutorialSlidePosition(struct tutorialSlide* this, Image tutorialImage) {
    FilePathList file = LoadDirectoryFiles("samouczek");
    this->numOfSlides = file.capacity;

    struct slidePositionParameters init = this->init;
    this->initposX = init.posX;
    this-> initx = init.x;
    this->tutorialImageHeight = tutorialImage.height;
    this->tutorialImageWidth = tutorialImage.width;

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
            .x = (int)this->descriptionBox.rec.x - 160,
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
            .x = (int)(this->descriptionBox.rec.x + this->descriptionBox.rec.width) + 150,
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

    this->page = 1;

    this->prev.isActive = (this->page == 1) ? 0 : 1;
    this->next.isActive = ((this->page + 1) >= this->numOfSlides) ? 0 : 1;
}

void DrawTutorialSlideBox(struct tutorialSlide* this, Texture2D imageAsTexture, char* title, char* description) {
    struct slidePositionParameters init = this->init;

    Vector2 texturePosition;
    texturePosition.x = (this->initx - this->initposX) / 2.0f;
    texturePosition.y = (this->top + this->height) / 10.0f + this->height;

    this->descriptionBox = (struct textBox){
        .rec = {
            .x = texturePosition.x,
            .y = texturePosition.y + imageAsTexture.height* (float)this->initx / imageAsTexture.width,
            .width = (float)init.width,
            .height = (float)GetScreenHeight() - (texturePosition.y + imageAsTexture.height * (float)this->initx / imageAsTexture.width) - 50
        },
        .textLeftCorner = (Vector2) {
            .x = texturePosition.x,
            .y = texturePosition.y + imageAsTexture.height * (float)this->initx / imageAsTexture.width,
        }
    };

    float size[2] = {
        MeasureTextEx(*this->font, title, (float)this->fontSize, (float)this->spaceing).x + (init.incX << 1),
        MeasureTextEx(*this->font, description, (float)this->fontSize, (float)this->spaceing).x + (init.incX << 1)
    };

    DrawRectangleRec(this->titleBox.rec, this->color);

    DrawRectangleLinesEx(this->titleBox.rec, (float)this->width, this->borderColor);

    DrawRectangleRec(this->descriptionBox.rec, this->backgroundColor);

    DrawRectangleLinesEx(this->descriptionBox.rec, (float)this->width, this->borderColor);

    DrawTextEx(*this->font, title, this->titleBox.textLeftCorner, size[0]/5, (float)this->spaceing, this->fontColor);
    DrawTextEx(*this->font, description, this->descriptionBox.textLeftCorner, size[1]/5, (float)this->spaceing, this->fontColor);
    DrawTextureEx(imageAsTexture, texturePosition, 0, (float)this->initx/imageAsTexture.width, WHITE);

    DrawButton(this->next);
    DrawButton(this->prev);

}

int UpdateTutorialSlideBox(struct tutorialSlide* this) {
    if (isMouseOver(this->prev)) {
        if(this->page > 1) this->page -= 1;
    }
    else if (isMouseOver(this->next)) {
        if (this->page <= this->numOfSlides) this->page += 1;
    }
    printf("          %i       ", this->page);
    this->prev.isActive = (this->page <= 1 ) ? 0 : 1;
    this->next.isActive = ((this->page + 1) > this->numOfSlides) ? 0 : 1;

    return this->page;

}
