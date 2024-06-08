#include <string.h>

#include "state.h"

#include "menuElements.h"

#include "saveData.h"
#include "animateAttack.h"

static void initializeRows(struct chooseAction *const this) {
    struct chooseActionPositionParameters init = this->init;

    float size[4] = {
        [NUM] = MeasureTextEx(*this->font, TextFormat("%i", this->attacksQuantity), (float)this->fontSize, (float)this->spaceing).x + (init.incX << 1),
        [NAME] = (float)init.width + (init.incX << 1)
    };

    const float height = this->fontSize + 2.0f * init.incY;
    const float top = init.y - (this->rowQuantity * height * init.posY) / 2;

    int i = 0;

    size[MAIN] = size[NUM] + size[NAME];

    this->row = malloc(sizeof(struct celle[4]) * this->rowQuantity);

    while (i < this->rowQuantity) {
        this->row[i][MAIN] = (struct celle){
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

        this->row[i][NUM] = (struct celle){
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

        this->row[i][NAME] = (struct celle){
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

        i += 1;
    }

    this->prevRec = (Rectangle){
        .x = 0
    };
}

void initializeChooseAction(struct chooseAction *const this) {
    initializeRows(this);

    this->chosenRow = -1;
    this->upperRow = 0;
}

static void freeRows(struct chooseAction *const this) {
    free(this->row);
}

void FreeChooseAction(struct chooseAction *const this) {
    freeRows(this);
}

void DrawChooseAction(const struct chooseAction *const this) {
    if (this->isActive) {
        int i = 0;
        int j = 0;

        while (i < this->rowQuantity) {
            DrawRectangleRec(this->row[i][MAIN].rec, this->color);

            j = 0;
            while (j < 2) {
                DrawRectangleLinesEx(this->row[i][j].rec, (float)this->wideness, this->inactiveBorderColor);
                j += 1;
            }

            DrawRectangleLinesEx(this->row[i][MAIN].rec, (float)this->wideness,
                this->chosenRow == i ? this->activeBorderColor :
                CheckCollisionPointRec(GetMousePosition(), this->row[i][MAIN].rec) ? this->hoverColor :
                this->inactiveBorderColor
            );

            if (i + this->upperRow < this->active->fighter.attackQuantity) {
                DrawTextEx(*this->font, TextFormat("%i", i + 1 + this->upperRow), this->row[i][NUM].textLeftCorner, (float)this->fontSize, (float)this->spaceing, this->fontColor);
                DrawTextEx(*this->font, (*this->attacks)[this->active->fighter.attacks[i + this->upperRow]].name, this->row[i][NAME].textLeftCorner, (float)this->fontSize, (float)this->spaceing, BLACK);
            }

            i += 1;
        }
    }
}

void AttackPlayer(struct chooseAction *const this, struct animateAttack *attack) {
    attack->isAttacked = 1;
    attack->attacker = this->active;
    attack->attacked = this->target;
    attack->attackID = rand() % attack->attacker->fighter.attackQuantity;
    attack->playerTurn = attack->playerTurn ? 0 : 1;

    struct fighterLabel *temp = this->active;
    this->active = this->target;
    this->target = temp;
}

void UpdateChooseActionScrool(struct chooseAction *const this) {
    static float scroll = 0.0f;

    if (this->isActive) {
        scroll -= GetMouseWheelMove();
        if (scroll < -1.0f) {
            if (this->upperRow > 0) {
                this->upperRow -= 1;
            }
            scroll = 0.0f;
        }
        else if (scroll > 1.0f) {
            if (this->upperRow + this->rowQuantity < this->active->fighter.attackQuantity) {
                this->upperRow += 1;
            }
            scroll = 0.0f;
        }
    }
}

int UpdateChooseAction(struct chooseAction *const this, struct animateAttack *attack) {
    int i = 0;
    int clicked = 0;

    if (this->isActive) {
        this->chosenRow = -1;
        while (i < this->rowQuantity) {
            if (CheckCollisionPointRec(GetMousePosition(), this->row[i][MAIN].rec)) {
                this->chosenRow = i;
                clicked |= 0x01;
                if (i + this->upperRow < this->active->fighter.attackQuantity) {
                    clicked |= 0x02;

                    attack->isAttacked = 1;
                    attack->attacker = this->active;
                    attack->attacked = this->target;

                    if (this->active->rest >= (*this->attacks)[this->active->fighter.attacks[i + this->upperRow]].force) {
                        attack->isAttacked = 1;
                        attack->attackID = i + this->upperRow;
                        attack->attacker = this->active;
                        attack->attacked = this->target;
                        attack->playerTurn = attack->playerTurn ? 0 : 1;

                        struct fighterLabel *temp = this->active;
                        this->active = this->target;
                        this->target = temp;
                    }
                }
            }

            i += 1;
        }

        if (clicked & 0x02 || ~clicked & 0x01) {
            this->isActive = 0;
            this->chosenRow = -1;
            this->upperRow = 0;
        }
    }

    return clicked;
}