#include <string.h>

#include "state.h"
#include "button.h"

#include "choiceBox.h"
#include "saveData.h"

static void loadSaves(struct choiceBox *const this) {
    FilePathList file = LoadDirectoryFiles("saves");
    int i = 0;

    this->dataQuantity = file.capacity;
    this->saveData = malloc(sizeof(struct saveData) * this->dataQuantity);

    while (i < this->dataQuantity) {
        initializeSaveData(&this->saveData[i], file.paths[i]);

        i += 1;
    }

    qsort(this->saveData, this->dataQuantity, sizeof(struct saveData), cmpSaveData);

    UnloadDirectoryFiles(file);
}

static void initializeRows(struct choiceBox *const this) {
    struct choiceBoxPositionParameters init = this->init;

    char buffor[9] = { 0 };

    float size[4] = {
        [NUM] = MeasureTextEx(*this->font, _itoa(this->dataQuantity, buffor, 10), (float)this->fontSize, (float)this->spaceing).x + (init.incX << 1),
        [NAME] = (float)init.width + (init.incX << 1),
        [DATE] = MeasureTextEx(*this->font, "99:99 99/99/9999", (float)this->fontSize, (float)this->spaceing).x + (init.incX << 1)
    };

    const float height = this->fontSize + 2.0f * init.incY;
    const float top = init.y - (this->rowQuantity * height * init.posY) / 2;

    int i = 0;

    size[MAIN] = size[NUM] + size[NAME] + size[DATE];

    this->row = malloc(sizeof(struct cell[4]) * this->rowQuantity);

    while (i < this->rowQuantity) {
        this->row[i][MAIN] = (struct cell){
            .rec = {
                .x = init.x - init.posX * size[MAIN] / 2.0f,
                .y = top + i * height,
                .width = size[MAIN],
                .height = height
            },
            .textLeftCorner = (Vector2) {
                .x = init.x - init.posX * size[MAIN] / 2.0f + init.incX,
                .y = top + i * height + init.incY
            }
        };

        this->row[i][NUM] = (struct cell){
            .rec = {
                .x = this->row[i][MAIN].rec.x,
                .y = top + i * height,
                .width = size[NUM],
                .height = height
            },
            .textLeftCorner = (Vector2) {
                .x = this->row[i][MAIN].rec.x + init.incX,
                .y = top + i * height + init.incY
            }
        };

        this->row[i][NAME] = (struct cell){
            .rec = {
                .x = this->row[i][NUM].rec.x + size[NUM],
                .y = top + i * height,
                .width = size[NAME],
                .height = height
            },
            .textLeftCorner = (Vector2) {
                .x = this->row[i][NUM].rec.x + size[NUM] + init.incX,
                .y = top + i * height + init.incY
            }
        };

        this->row[i][DATE] = (struct cell){
            .rec = {
                .x = this->row[i][NAME].rec.x + size[NAME],
                .y = top + i * height,
                .width = size[DATE],
                .height = height
            },
            .textLeftCorner = (Vector2) {
                .x = this->row[i][NAME].rec.x + size[NAME] + init.incX,
                .y = top + i * height + init.incY
            }
        };

        i += 1;
    }

    this->prevRec = (Rectangle){
        .x = 0
    };
}

static void initializeButtons(struct choiceBox *const this) {
    this->prev = (struct button){
        .text = "Poprzednie",
        .init = {
            .x = (int)this->row[0][MAIN].rec.x,
            .y = (int)(this->row[this->rowQuantity - 1][MAIN].rec.y + this->row[this->rowQuantity - 1][MAIN].rec.height),
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
        .text = "Następne",
        .init = {
            .x = (int)(this->row[0][MAIN].rec.x + this->row[0][MAIN].rec.width),
            .y = (int)(this->row[this->rowQuantity - 1][MAIN].rec.y + this->row[this->rowQuantity - 1][MAIN].rec.height),
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

void initializeChoiceBox(struct choiceBox *const this) {
    initializeRows(this);
    initializeButtons(this);
    loadSaves(this);

    this->chosenRow = -1;
    this->page = 0;
}

static void unloadSaves(struct choiceBox *const this) {
    int i = 0;

    while (i < this->dataQuantity) {
        freeSaveData(&this->saveData[i]);

        i += 1;
    }

    free(this->saveData);
}

static void freeRows(struct choiceBox *const this) {
    free(this->row);
}

void freeChoiceBox(struct choiceBox *const this) {
    unloadSaves(this);
    freeRows(this);
}

void DrawChoiceBox(struct choiceBox *const this) {
    int i = 0;
    int j = 0;

    while (i < this->rowQuantity) {
        DrawRectangleRec(this->row[i][MAIN].rec, this->color);

        j = 0;
        while (j < 3) {
            DrawRectangleLinesEx(this->row[i][j].rec, (float)this->wideness, this->inactiveBorderColor);
            j += 1;
        }

        DrawRectangleLinesEx(this->row[i][MAIN].rec, (float)this->wideness,
            this->chosenRow == i ? this->activeBorderColor :
            CheckCollisionPointRec(GetMousePosition(), this->row[i][MAIN].rec) ? this->hoverColor :
            this->inactiveBorderColor
        );

        if (i + this->page * this->rowQuantity < this->dataQuantity) {
            DrawTextEx(*this->font, TextFormat("%i", i + 1 + this->page * this->rowQuantity), this->row[i][NUM].textLeftCorner, (float)this->fontSize, (float)this->spaceing, this->fontColor);
            DrawTextEx(*this->font, this->saveData[i + this->page * this->rowQuantity].text, this->row[i][NAME].textLeftCorner, (float)this->fontSize, (float)this->spaceing, this->fontColor);
            DrawTextEx(*this->font, assembleDate(&this->saveData[i + this->page * this->rowQuantity]), this->row[i][DATE].textLeftCorner, (float)this->fontSize, (float)this->spaceing, this->fontColor);
        }

        i += 1;
    }

    DrawButton(this->next);
    DrawButton(this->prev);

    if (this->page == 0) {
        DrawRectangleRec(this->prev.boxRectangle, (Color) {100, 100, 100, 100});
    }
    if ((this->page + 1) * this->rowQuantity >= this->dataQuantity) {
        DrawRectangleRec(this->next.boxRectangle, (Color) {100, 100, 100, 100});
    }
}

void UpdateChoiceBox(struct choiceBox *const this, struct menuInfo *info) {
    int i = 0;

    this->chosenRow = -1;
    while (i < this->rowQuantity) {
        if (CheckCollisionPointRec(GetMousePosition(), this->row[i][MAIN].rec)) {
            strcpy(info->saveName, this->saveData[i + this->rowQuantity * this->page].text);
            this->chosenRow = i;
        }

        i += 1;
    }

    if (isMouseOver(this->prev)) {
        if (this->page > 0) {
            this->page -= 1;
        }
    }

    if (isMouseOver(this->next)) {
        if ((this->page + 1) * this->rowQuantity < this->dataQuantity) {
            this->page += 1;
        }
    }
}