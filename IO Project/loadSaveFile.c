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

static void loadBody(FILE *playerFile, struct character *character) {
    int i = 0;

    while (i < 10) {
        fscanf(playerFile, "%i", &character->bodyPart[i]);

        i += 1;
    }
}

static void loadArmor(FILE *playerFile, struct character *character) {
    int i = 0;

    while (i < 9) {
        fscanf(playerFile, "%i", &character->armorPart[i]);

        i += 1;
    }
}

static void loadCharacter(struct character *character, const char *characterSave, float x, float z) {
    FILE *playerFile = fopen(characterSave, "r");
    struct Object2D *object = &character->object;

    *object = (struct Object2D){
        .position = (Vector3) {
            .x = x,
            .y = 0.0f,
            .z = z
        },
        .texture = malloc(sizeof(Texture2D))
    };

    character->direction = 0;

    fscanf(playerFile, "%[^\n]", character->name);
    fscanf(playerFile, "%f %f", &object->sizeV.x, &object->sizeV.y);

    loadBody(playerFile, character);
    loadArmor(playerFile, character);

    fscanf(playerFile, "%i", &character->weapon);

    fclose(playerFile);
}

static void createEnemies(FILE *file, struct playInfo *info) {
    int i = 0;
    int id = 0;
    float x = 0.0f;
    float y = 0.0f;

    fscanf(file, "%i", &info->enemyQuantity);
    info->enemies = malloc(sizeof(struct character) * info->enemyQuantity);

    while (i < info->enemyQuantity) {
        fscanf(file, "%i %i %f %f", &id, &info->enemies[i].dialog, &x, &y);

        info->enemies[i].ID = id;
        loadCharacter(&info->enemies[i], TextFormat("dane\\postacie\\%i.txt", id), x, y);
        assemblePlayerTexture(info, &info->enemies[i]);

        i += 1;
    }
}

static void loadSellers(FILE *file, struct playInfo *info) {
    int i = 0;
    float x = 0.0f;
    float z = 0.0f;

    fscanf(file, "%i", &info->sellersQuantity);
    info->shops = malloc(sizeof(struct seller) * info->sellersQuantity);

    while (i < info->sellersQuantity) {

        fscanf(file, "%i %i %i %f %f", 
            &info->shops[i].character.ID, 
            &info->shops[i].shopID, 
            &info->shops[i].character.dialog, 
            &x,
            &z);

        loadCharacter(&info->shops[i].character, TextFormat("dane\\postacie\\%i.txt", info->shops[i].character.ID), x, z);
        assemblePlayerTexture(info, &info->shops[i].character);

        i += 1;
    }
}

static void loadShop(int shopEquipment[10][3], const char *path) {
    FILE *file = fopen(path, "r");
    int i = 0;

    while (i < 10) {
        fscanf(file, "%i", &shopEquipment[i][0]);

        if (shopEquipment[i][0] != 0) {
            fscanf(file, "%i", &shopEquipment[i][1]);

            if (shopEquipment[i][0] == 2) {
                fscanf(file, "%i", &shopEquipment[i][2]);
            }
        }

        i += 1;
    }

    fclose(file);
}

static void loadShops(struct playInfo *this) {
    FilePathList f = LoadDirectoryFiles(TextFormat("saves\\%s\\sklepy", this->saveName));
    int i = 0;

    this->shopQuantity = f.capacity;

    this->shopEquipment = malloc(sizeof(int[10][3]) * this->shopQuantity);

    while (i < this->shopQuantity) {
        loadShop(this->shopEquipment[i], TextFormat("saves\\%s\\sklepy\\%i.txt", this->saveName, i));

        i += 1;
    }

    UnloadDirectoryFiles(f);
}

static void loadEquipment(struct player *player, const char *fileName) {
    FILE *file = fopen(fileName, "r");
    int i = 0;

    while (i < 25) {
        fscanf(file, "%i", &player->equipment[i][0]);

        if (player->equipment[i][0] != 0) {
            fscanf(file, "%i", &player->equipment[i][1]);

            if (player->equipment[i][0] == 2) {
                fscanf(file, "%i", &player->equipment[i][2]);
            }
        }

        i += 1;
    }

    fclose(file);
}

static void loadPlayer(struct playInfo *info, const char *saveName) {
    loadCharacter(&info->player.character, TextFormat("saves\\%s\\postaæ.txt", saveName), 4.0f, 0.0f);
    assemblePlayerTexture(info, &info->player.character);
    loadEquipment(&info->player, TextFormat("saves\\%s\\ekwipunek.txt", saveName));
    createDate(TextFormat("saves\\%s\\date.txt", saveName));

    info->player.speedY = 0;
}

void loadSaveFile(struct playInfo *this, const char *saveName) {
    FILE *mapFile = fopen(TextFormat("saves\\%s\\mapy\\0.txt", saveName), "r");

    loadShops(this);

    createEnemies(mapFile, this);
    loadSellers(mapFile, this);

    loadPlayer(this, saveName);

    fclose(mapFile);
}