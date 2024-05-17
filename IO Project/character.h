#ifndef CHARACTER_H
#define CHARACTER_H

#include <raylib.h>

#include "object2D.h"

struct character {
	char* name;
	int health;
	int attack;
	int exhaustion;
	struct Object2D object;
	//Texture2D *head;
	//Texture2D *body;
};

#endif