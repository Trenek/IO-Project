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

static void saveEnemies(FILE *file, struct playInfo *info) {
    int i = 0;

    fprintf(file, "%i\n", info->enemyQuantity);
    while (i < info->enemyQuantity) {
        fprintf(file, "% 4s%i %i %f %f\n", "", info->enemies[i].ID, info->enemies[i].dialog, info->enemies[i].object.position.x, info->enemies[i].object.position.z);

        i += 1;
    }
}

static void saveShops(FILE *file, struct playInfo *info) {
    int i = 0;

    fprintf(file, "%i", info->shopsQuantity);
    while (i < info->shopsQuantity) {
        fprintf(file, "% 4s%i %i %f %f\n", "", info->shops[i].ID, info->shops[i].dialog, info->shops[i].object.position.x, info->shops[i].object.position.z);

        i += 1;
    }
}

static void saveMap(struct playInfo *info, const char *saveName) {
    FILE *mapFile = fopen(TextFormat("saves\\%s\\mapy\\0.txt", saveName), "w");

    saveEnemies(mapFile, info);
    saveShops(mapFile, info);

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

            if (player->equipment[i][1] == 2) {
                fprintf(file, "%i ", player->equipment[i][2]);
            }
        }

        fprintf(file, "\n");

        i += 1;
    }

    fclose(file);
}

void saveSaveFile(struct playInfo *this, const char *saveName) {
    saveMap(this, saveName);
    saveCharacter(&this->player.character, TextFormat("saves\\%s\\postaæ.txt", saveName));
    saveEquipment(&this->player, TextFormat("saves\\%s\\ekwipunek.txt", saveName));
    createDate(TextFormat("saves\\%s\\date.txt", saveName));
}