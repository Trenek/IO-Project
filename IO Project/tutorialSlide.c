#include <raylib.h>

#include "button.h"
#include "tutorialSlide.h"

static void CalculateTutorialSlidePosition(struct tutorialSlide *this) {
    FilePathList file = LoadDirectoryFiles("dane\\samouczek");
    struct slidePositionParameters init = this->init;

    float height = this->fontSize + 2.0f * init.incY;
    float top = (float)init.y - (init.height * init.posY) / 2.0f;

    this->numOfSlides = file.capacity;

    this->image = LoadTexture("dane\\samouczek\\tip1\\img.png");
    this->description = LoadFileText("dane\\samouczek\\tip1\\description.txt");
    this->title = LoadFileText("dane\\samouczek\\tip1\\title.txt");

    this->texturePosition = (Vector2) {
        .x = init.x - (init.posX * init.width) / 2.0f,
        .y = top + height
    };

    this->titleBox = (struct textBox){
        .rec = {
            .x = this->texturePosition.x,
            .y = top,
            .width = (float)init.width,
            .height = height
        },
        .textLeftCorner = {
            .x = this->texturePosition.x + init.incX,
            .y = top + init.incY
        }
    };

    this->descriptionBox = (struct textBox){
        .rec = {
            .x = this->texturePosition.x,
            .y = this->texturePosition.y + this->image.height * init.x / this->image.width,
            .width = (float)init.width,
            .height = init.height - height - this->image.height
        },
        .textLeftCorner = {
            .x = this->texturePosition.x + init.incX,
            .y = this->texturePosition.y + this->image.height * init.x / this->image.width + init.incY
        }
    };

    UnloadDirectoryFiles(file);
}

static void initializeButtons(struct tutorialSlide *this) {
    this->prev = (struct button){
        .text = "Poprzednie",
        .isActive = 1,
        .init = {
            .x = (int)this->descriptionBox.rec.x,
            .y = (int)(this->descriptionBox.rec.y + this->descriptionBox.rec.height),
            .incX = 10,
            .incY = 10,
            .posX = 3,
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
            .posX = -1,
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

void initializeTutorialSlideBox(struct tutorialSlide *this) {
    CalculateTutorialSlidePosition(this);
    initializeButtons(this);

    this->page = 1;

    this->prev.isActive = this->page != 1;
    this->next.isActive = (this->page + 1) < this->numOfSlides;
}

void freeTutorialSlideBox(struct tutorialSlide *this) {
    UnloadTexture(this->image);
    UnloadFileText(this->description);
    UnloadFileText(this->title);
}

void DrawTutorialSlideBox(struct tutorialSlide *this) {
    DrawRectangleRec(this->titleBox.rec, this->color);

    DrawRectangleLinesEx(this->titleBox.rec, (float)this->lineWidth, this->borderColor);

    DrawRectangleRec(this->descriptionBox.rec, this->backgroundColor);

    DrawRectangleLinesEx(this->descriptionBox.rec, (float)this->lineWidth, this->borderColor);

    DrawTextEx(*this->font, this->title, this->titleBox.textLeftCorner, (float)this->fontSize, (float)this->spaceing, this->fontColor);
    DrawTextEx(*this->font, this->description, this->descriptionBox.textLeftCorner, (float)this->fontSize, (float)this->spaceing, this->fontColor);
    DrawTextureEx(this->image, this->texturePosition, 0, (float)this->titleBox.rec.width/this->image.width, WHITE);

    DrawButton(this->next);
    DrawButton(this->prev);
}

void UpdateTutorialSlideBox(struct tutorialSlide *this) {
    bool changed = false;

    if (isMouseOver(this->prev)) {
        if (this->page > 1) {
            this->page -= 1;

            changed = true;
        }
    }
    else if (isMouseOver(this->next)) {
        if (this->page <= this->numOfSlides) {
            this->page += 1;

            changed = true;
        }
    }

    this->prev.isActive = (this->page <= 1 ) ? 0 : 1;
    this->next.isActive = ((this->page + 1) > this->numOfSlides) ? 0 : 1;

    if (changed) {
        UnloadFileText(this->title);
        UnloadFileText(this->description);
        UnloadTexture(this->image);

        this->image = LoadTexture(TextFormat("dane\\samouczek\\tip%i\\img.png", this->page));
        this->description = LoadFileText(TextFormat("dane\\samouczek\\tip%i\\description.txt", this->page));
        this->title = LoadFileText(TextFormat("dane\\samouczek\\tip%i\\title.txt", this->page));
    }
}
