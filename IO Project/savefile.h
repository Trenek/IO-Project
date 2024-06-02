#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <stdbool.h>

#include "character.h"
#include "player.h"
#include "floor.h"
#include "wall.h"
#include "seller.h"

struct Achievement {
    char name[200];
    char description[300];
    int status;
    int requirementsCount;
    char **requirements;
};

struct SaveFile {
    char *const saveName;
    int mapID;

    struct player player;

    int(*shopEquipment)[10][3];
    int shopQuantity;

    struct map {
        struct floors *floors;
        int floorsQuantity;

        struct wall *walls;
        int wallQuantity;

        struct character *enemies;
        int enemyQuantity;

        struct seller *sellers;
        int sellersQuantity;
    };

    int achievementsQuantity;
    struct Achievement *achievements;
};

bool CreateNewSave(const char *const saveName, const char *const characterName, const int bodyParts[10]);
void LoadSaveFile(struct SaveFile *this, struct Resources *resources);
void UnloadSaveFile(struct SaveFile *this);
void SaveSaveFile(struct SaveFile *this);

#endif