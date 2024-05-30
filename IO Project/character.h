#ifndef CHARACTER_H
#define CHARACTER_H

#include <raylib.h>

#include "object2D.h"

struct Resources;

struct character {
	char name[130];
	int health;
	int attack;
	int exhaustion;
	struct Object2D object;

	int ID;

	int dialog;
	int direction;
	int bodyPart[10];
	int armorPart[9];
	int weapon;
};

void UnloadCharacter(struct character *character);
void assemblePlayerTexture(struct Resources *info, struct character *character);

#endif