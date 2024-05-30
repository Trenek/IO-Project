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

static void loadCharacterBody(FILE *playerFile, struct character *character) {
    int i = 0;

    while (i < 10) {
        fscanf(playerFile, "%i", &character->bodyPart[i]);

        i += 1;
    }
}

static void loadCharacterArmor(FILE *playerFile, struct character *character) {
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

    loadCharacterBody(playerFile, character);
    loadCharacterArmor(playerFile, character);

    fscanf(playerFile, "%i", &character->weapon);

    fclose(playerFile);
}

static void loadFloors(FILE *file, struct playInfo *info) {
    int i = 0;

    fscanf(file, "%i", &info->floorsQuantity);
    info->floors = malloc(sizeof(struct character) * info->floorsQuantity);

    while (i < info->floorsQuantity) {
        fscanf(file, "%i %f %f %f %f %f %f", 
            &info->floors[i].ID,
            &info->floors[i].object.sizeV.x,
            &info->floors[i].object.sizeV.y,
            &info->floors[i].object.position.x,
            &info->floors[i].object.position.z,
            &info->floors[i].actualSize.x,
            &info->floors[i].actualSize.y
        );

        info->floors[i].object.position.y = 0.0f;

        info->floors[i].object.texture = &info->resources->floorTextures[info->floors[i].ID];

        i += 1;
    }
}

static void loadWalls(FILE *file, struct playInfo *info) {
    int i = 0;

    fscanf(file, "%i", &info->wallQuantity);
    info->walls = malloc(sizeof(struct character) * info->wallQuantity);

    while (i < info->wallQuantity) {
        fscanf(file, "%i %f %f %f %f %f %f %f %f",
            &info->walls[i].ID,
            &info->walls[i].object.sizeV.x,
            &info->walls[i].object.sizeV.y,
            &info->walls[i].object.position.x,
            &info->walls[i].object.position.y,
            &info->walls[i].object.position.z,
            &info->walls[i].endPosition.x,
            &info->walls[i].endPosition.y,
            &info->walls[i].endPosition.z
        );

        info->walls[i].object.texture = &info->resources->wallTextures[info->walls[i].ID];

        i += 1;
    }
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
    loadCharacter(&info->player.character, TextFormat("saves\\%s\\postaæ.txt", saveName), info->player.character.object.position.x, info->player.character.object.position.z);
    assemblePlayerTexture(info, &info->player.character);
    loadEquipment(&info->player, TextFormat("saves\\%s\\ekwipunek.txt", saveName));
    createDate(TextFormat("saves\\%s\\date.txt", saveName));

    info->player.speedY = 0;
    info->player.r = 5;
    info->player.b = 0;
    info->player.a = 30 * PI / 180;
}

static void loadPosition(struct playInfo *this, const char *saveName) {
    FILE *position = fopen(TextFormat("saves\\%s\\mapy\\position.txt", saveName), "r");

    fscanf(position, "%i %f %f", &this->mapID, &this->player.character.object.position.x, &this->player.character.object.position.z);

    fclose(position);
}

static void loadMap(struct playInfo *this, const char *saveName) {
    FILE *mapFile = fopen(TextFormat("saves\\%s\\mapy\\%i.txt", saveName, this->mapID), "r");

    loadFloors(mapFile, this);
    loadWalls(mapFile, this);
    createEnemies(mapFile, this);
    loadSellers(mapFile, this);

    fclose(mapFile);
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


void loadSaveFile(struct playInfo *this, const char *saveName) {
    loadPosition(this, saveName);

    loadShops(this);
    loadMap(this, saveName);

    loadPlayer(this, saveName);
}