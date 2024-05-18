#ifndef CHARACTER_H
#define CHARACTER_H

#include <raylib.h>

#include "object2D.h"

struct playInfo;

struct character {
	char name[130];
	int health;
	int attack;
	int exhaustion;
	struct Object2D object;

	int direction;
	int bodyPart[10];
};

void assemblePlayerTexture(struct playInfo *info, struct character *character);

#endif