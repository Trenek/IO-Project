#ifndef ANIMATE_ATTACK_H
#define ANIMATE_ATTACK_H

struct fighterLabel;
struct playInfo;

struct animateAttack {
    int isAttacked;
    int playerTurn; // 0 - player, 1 - enemy
    int attackID;

    struct fighterLabel *attacker;
    struct fighterLabel *attacked;
};

void animateAttack(struct playInfo *info, struct animateAttack *attack);

#endif