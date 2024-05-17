#ifndef CHARACTER_H
#define CHARACTER_H

#include <raylib.h>

#include "object2D.h"

struct character {
	int health;
	int attack;
	int exhaustion;
	struct Object2D object;
};

#endif