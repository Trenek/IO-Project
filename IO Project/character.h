#ifndef CHARACTER_H
#define CHARACTER_H

#include <raylib.h>

#include "object2D.h"

struct playInfo;
struct menuInfo;

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

void unloadCharacter(struct character *character);
void assemblePlayerTexture(struct playInfo *info, struct character *character); 
void mainAssemblePlayerTexture(struct menuInfo *info, struct character *character);

#endif