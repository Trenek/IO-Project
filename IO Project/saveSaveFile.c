#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "savefile.h"
#include "playState.h"

#include "player.h"

static void createDate(const char *const saveName) {
    FILE *file = fopen(saveName, "w");
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    fprintf(file, "%i ", tm.tm_year + 1900);
    fprintf(file, "%i ", tm.tm_mon + 1);
    fprintf(file, "%i ", tm.tm_mday);
    fprintf(file, "%i ", tm.tm_hour);
    fprintf(file, "%i ", tm.tm_min);
    fprintf(file, "%i", tm.tm_sec);

    fclose(file);
}

static void saveFloors(FILE *file, struct playInfo *info) {
    int i = 0;

    fprintf(file, "%i\n", info->floorsQuantity);
    while (i < info->floorsQuantity) {
        fprintf(file, "% 4s%i %f %f %f %f %f %f\n", "", 
            info->floors[i].ID, 
            info->floors[i].object.sizeV.x,
            info->floors[i].object.sizeV.y,
            info->floors[i].object.position.x,
            info->floors[i].object.position.z,
            info->floors[i].actualSize.x,
            info->floors[i].actualSize.y
        );

        i += 1;
    }
}

static void saveWalls(FILE *file, struct playInfo *info) {
    int i = 0;

    fprintf(file, "%i\n", info->wallQuantity);
    while (i < info->wallQuantity) {
        fprintf(file, "% 4s%i %f %f %f %f %f %f %f %f\n", "",
            info->walls[i].ID,
            info->walls[i].object.sizeV.x,
            info->walls[i].object.sizeV.y,
            info->walls[i].object.position.x,
            info->walls[i].object.position.y,
            info->walls[i].object.position.z,
            info->walls[i].endPosition.x,
            info->walls[i].endPosition.y,
            info->walls[i].endPosition.z
        );

        i += 1;
    }
}

static void saveEnemies(FILE *file, struct playInfo *info) {
    int i = 0;

    fprintf(file, "%i\n", info->enemyQuantity);
    while (i < info->enemyQuantity) {
        fprintf(file, "% 4s%i %i %f %f\n", "", info->enemies[i].ID, info->enemies[i].dialog, info->enemies[i].object.position.x, info->enemies[i].object.position.z);

        i += 1;
    }
}

static void saveSellers(FILE *file, struct playInfo *info) {
    int i = 0;

    fprintf(file, "%i", info->sellersQuantity);
    while (i < info->sellersQuantity) {
        fprintf(file, "% 4s%i %i %i %f %f\n", "", info->shops[i].character.ID, info->shops[i].shopID, info->shops[i].character.dialog, info->shops[i].character.object.position.x, info->shops[i].character.object.position.z);

        i += 1;
    }
}

static void saveMap(struct playInfo *info, const char *saveName) {
    FILE *mapFile = fopen(TextFormat("saves\\%s\\mapy\\0.txt", saveName), "w");

    saveFloors(mapFile, info);
    saveWalls(mapFile, info);
    saveEnemies(mapFile, info);
    saveSellers(mapFile, info);

    fclose(mapFile);
}

static void saveBody(FILE *playerFile, struct character *character) {
    int i = 0;

    while (i < 10) {
        fprintf(playerFile, "%i\n", character->bodyPart[i]);

        i += 1;
    }
    fprintf(playerFile, "\n");
}

static void saveArmor(FILE *playerFile, struct character *character) {
    int i = 0;

    while (i < 9) {
        fprintf(playerFile, "%i\n", character->armorPart[i]);

        i += 1;
    }
    fprintf(playerFile, "\n");
}

void saveCharacter(struct character *character, const char *characterSave) {
    FILE *playerFile = fopen(characterSave, "w");
    struct Object2D *object = &character->object;

    fprintf(playerFile, "%s\n", character->name);
    fprintf(playerFile, "%f %f\n\n", object->sizeV.x, object->sizeV.y);

    saveBody(playerFile, character);
    saveArmor(playerFile, character);

    fprintf(playerFile, "%i", character->weapon);

    fclose(playerFile);
}

static void saveEquipment(struct player *player, const char *fileName) {
    FILE *file = fopen(fileName, "w");
    int i = 0;

    while (i < 25) {
        fprintf(file, "% 4s%i ", "", player->equipment[i][0]);

        if (player->equipment[i][0] != 0) {
            fprintf(file, "%i ", player->equipment[i][1]);

            if (player->equipment[i][0] == 2) {
                fprintf(file, "%i ", player->equipment[i][2]);
            }
        }

        fprintf(file, "\n");

        i += 1;
    }

    fclose(file);
}

static void saveShop(int shopEQ[10][3], const char *fileName) {
    FILE *file = fopen(fileName, "w");
    int i = 0;

    while (i < 10) {
        fprintf(file, "% 4s%i ", "", shopEQ[i][0]);

        if (shopEQ[i][0] != 0) {
            fprintf(file, "%i ", shopEQ[i][1]);

            if (shopEQ[i][0] == 2) {
                fprintf(file, "%i ", shopEQ[i][2]);
            }
        }

        fprintf(file, "\n");

        i += 1;
    }

    fclose(file);
}

static void saveShops(struct playInfo *this, const char *saveName) {
    int i = 0;

    while (i < this->shopQuantity) {
        saveShop(this->shopEquipment[i], TextFormat("saves\\%s\\sklepy\\%i.txt", saveName, i));

        i += 1;
    }
}

void savePosition(struct playInfo *this, const char *saveName) {
    FILE *file = fopen(TextFormat("saves\\%s\\mapy\\position.txt", saveName), "w");

    fprintf(file, "%i %f %f", this->mapID, this->player.character.object.position.x, this->player.character.object.position.z);

    fclose(file);
}

void saveSaveFile(struct playInfo *this, const char *saveName) {
    saveShops(this, saveName);
    savePosition(this, saveName);
    saveMap(this, saveName);
    saveCharacter(&this->player.character, TextFormat("saves\\%s\\postaæ.txt", saveName));
    saveEquipment(&this->player, TextFormat("saves\\%s\\ekwipunek.txt", saveName));
    createDate(TextFormat("saves\\%s\\date.txt", saveName));
}