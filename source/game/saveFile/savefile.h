#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <stdbool.h>

#include "player.h"
#include "floor.h"
#include "wall.h"
#include "character.h"
#include "seller.h"
#include "ceiling.h"

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

        struct ceiling *ceiling;
        int ceilingQuantity;

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

int CreateNewSave(const char *const saveName, const char *const characterName, const int bodyParts[10], int difficultyLevel);
void LoadSaveFile(struct SaveFile *this, struct Resources *resources);
void UnloadSaveFile(struct SaveFile *this);
void SaveSaveFile(struct SaveFile *this);

#endif