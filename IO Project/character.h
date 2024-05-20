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

	int dialog;
	int direction;
	int bodyPart[10];
	int armorPart[9];
	int weapon;
};

void loadCharacter(struct character *character, const char *characterSave, float x, float z);
void unloadCharacter(struct character *character);
void assemblePlayerTexture(struct playInfo *info, struct character *character);

#endif