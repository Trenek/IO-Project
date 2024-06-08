#ifndef CHOOSEACTION_H
#define CHOOSEACTION_H

#include <raylib.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct saveData;
struct menuInfo;

struct chooseActionPositionParameters {
    int x;
    int y;
    int width;
    int incX;
    int incY;
    int posX;
    int posY;
};

struct celle {
    Rectangle rec;
    Vector2 textLeftCorner;
};

struct attack;
struct chooseAction {
    int rowQuantity;
    int wideness;

    int isActive;

    struct attack **attacks;
    int attacksQuantity;

    struct fighterLabel *active;
    struct fighterLabel *target;

    union {
        struct chooseActionPositionParameters init;
        struct {
            int upperRow;
            int chosenRow;

            struct celle(*row)[4];

            Rectangle prevRec;
            Rectangle nextRec;
        };
    };

    Font *font;
    Color fontColor;
    int fontSize;
    int spaceing;

    Color color;
    Color activeBorderColor;
    Color inactiveBorderColor;
    Color hoverColor;
};

struct animateAttack {
    int isAttacked;
    int playerTurn; // 0 - player, 1 - enemy
    int attackID;

    struct fighterLabel *attacker;
    struct fighterLabel *attacked;
};

void initializeChooseAction(struct chooseAction *const this);
void FreeChooseAction(struct chooseAction *const this);

void DrawChooseAction(const struct chooseAction *const this);
void UpdateChooseActionScrool(struct chooseAction *const this);
int UpdateChooseAction(struct chooseAction *const this, struct animateAttack *attack);
void AttackPlayer(struct chooseAction *const this, struct animateAttack *attack);

#endif