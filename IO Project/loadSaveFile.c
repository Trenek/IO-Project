#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "savefile.h"
#include "resources.h"

static void CreateDate(struct SaveFile *this) {
    FILE *file = fopen(TextFormat("saves\\%s\\date.txt", this->saveName), "w");
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

static void LoadCharacterBody(FILE *playerFile, struct character *character) {
    int i = 0;

    while (i < 10) {
        fscanf(playerFile, "%i", &character->bodyPart[i]);

        i += 1;
    }
}

static void LoadCharacterArmor(FILE *playerFile, struct character *character) {
    int i = 0;

    while (i < 9) {
        fscanf(playerFile, "%i", &character->armorPart[i]);

        i += 1;
    }
}

static void LoadCharacter(struct character *character, const char *characterSave, float x, float z) {
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

    LoadCharacterBody(playerFile, character);
    LoadCharacterArmor(playerFile, character);

    fscanf(playerFile, "%i", &character->weapon);

    fclose(playerFile);
}

static void LoadEquipment(struct player *player, const char *fileName) {
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

static void LoadPosition(struct SaveFile *this) {
    FILE *position = fopen(TextFormat("saves\\%s\\mapy\\position.txt", this->saveName), "r");

    fscanf(position, "%i %f %f", &this->mapID, &this->player.character.object.position.x, &this->player.character.object.position.z);

    fclose(position);
}

static void LoadPlayer(struct SaveFile *this, struct Resources *resources) {
    LoadCharacter(&this->player.character, TextFormat("saves\\%s\\postaæ.txt", this->saveName), this->player.character.object.position.x, this->player.character.object.position.z);
    assemblePlayerTexture(resources, &this->player.character);
    LoadEquipment(&this->player, TextFormat("saves\\%s\\ekwipunek.txt", this->saveName));
    LoadPosition(this);

    this->player.speedY = 0;
    this->player.r = 5;
    this->player.b = 0;
    this->player.a = 30 * PI / 180;
}

static void LoadShop(int shopEquipment[10][3], const char *path) {
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

static void LoadShops(struct SaveFile *this) {
    FilePathList f = LoadDirectoryFiles(TextFormat("saves\\%s\\sklepy", this->saveName));
    int i = 0;

    this->shopQuantity = f.capacity;

    this->shopEquipment = malloc(sizeof(int[10][3]) * this->shopQuantity);

    while (i < this->shopQuantity) {
        LoadShop(this->shopEquipment[i], TextFormat("saves\\%s\\sklepy\\%i.txt", this->saveName, i));

        i += 1;
    }

    UnloadDirectoryFiles(f);
}

static void LoadFloors(FILE *file, struct SaveFile *this, struct Resources *resources) {
    int i = 0;

    fscanf(file, "%i", &this->floorsQuantity);
    this->floors = malloc(sizeof(struct character) * this->floorsQuantity);

    while (i < this->floorsQuantity) {
        fscanf(file, "%i %f %f %f %f %f %f %f",
            &this->floors[i].ID,
            &this->floors[i].object.sizeV.x,
            &this->floors[i].object.sizeV.y,
            &this->floors[i].object.position.y,

            &this->floors[i].object.position.x,
            &this->floors[i].object.position.z,
            &this->floors[i].actualSize.x,
            &this->floors[i].actualSize.y
        );

        this->floors[i].object.texture = &resources->floors[this->floors[i].ID];

        i += 1;
    }
}

static void LoadCeilings(FILE *file, struct SaveFile *this, struct Resources *resources) {
    int i = 0;

    fscanf(file, "%i", &this->ceilingQuantity);
    this->ceiling = malloc(sizeof(struct character) * this->ceilingQuantity);

    while (i < this->ceilingQuantity) {
        fscanf(file, "%i %f %f %f %f %f %f %f",
            &this->ceiling[i].ID,
            &this->ceiling[i].object.sizeV.x,
            &this->ceiling[i].object.sizeV.y,
            &this->ceiling[i].object.position.y,
            &this->ceiling[i].object.position.x,
            &this->ceiling[i].object.position.z,
            &this->ceiling[i].actualSize.x,
            &this->ceiling[i].actualSize.y
        );

        this->ceiling[i].object.texture = &resources->ceiling[this->ceiling[i].ID];

        i += 1;
    }
}

static void LoadWalls(FILE *file, struct SaveFile *this, struct Resources *resources) {
    int i = 0;

    fscanf(file, "%i", &this->wallQuantity);
    this->walls = malloc(sizeof(struct character) * this->wallQuantity);

    while (i < this->wallQuantity) {
        fscanf(file, "%i %f %f %f %f %f %f %f %f",
            &this->walls[i].ID,
            &this->walls[i].object.sizeV.x,
            &this->walls[i].object.sizeV.y,
            &this->walls[i].object.position.x,
            &this->walls[i].object.position.y,
            &this->walls[i].object.position.z,
            &this->walls[i].endPosition.x,
            &this->walls[i].endPosition.y,
            &this->walls[i].endPosition.z
        );

        this->walls[i].object.texture = &resources->walls[this->walls[i].ID];

        i += 1;
    }
}

static void LoadEnemies(FILE *file, struct SaveFile *this, struct Resources *resources) {
    int i = 0;
    int id = 0;
    float x = 0.0f;
    float y = 0.0f;

    fscanf(file, "%i", &this->enemyQuantity);
    this->enemies = malloc(sizeof(struct character) * this->enemyQuantity);

    while (i < this->enemyQuantity) {
        fscanf(file, "%i %i %f %f", &id, &this->enemies[i].dialog, &x, &y);

        this->enemies[i].ID = id;
        LoadCharacter(&this->enemies[i], TextFormat("dane\\postacie\\%i.txt", id), x, y);
        assemblePlayerTexture(resources, &this->enemies[i]);

        i += 1;
    }
}

static void LoadSellers(FILE *file, struct SaveFile *this, struct Resources *resources) {
    int i = 0;
    float x = 0.0f;
    float z = 0.0f;

    fscanf(file, "%i", &this->sellersQuantity);
    this->sellers = malloc(sizeof(struct seller) * this->sellersQuantity);

    while (i < this->sellersQuantity) {

        fscanf(file, "%i %i %i %f %f",
            &this->sellers[i].character.ID,
            &this->sellers[i].shopID,
            &this->sellers[i].character.dialog,
            &x,
            &z);

        LoadCharacter(&this->sellers[i].character, TextFormat("dane\\postacie\\%i.txt", this->sellers[i].character.ID), x, z);
        assemblePlayerTexture(resources, &this->sellers[i].character);

        i += 1;
    }
}

static void LoadMap(struct SaveFile *this, struct Resources *resources) {
    FILE *mapFile = fopen(TextFormat("saves\\%s\\mapy\\%i.txt", this->saveName, this->mapID), "r");

    LoadFloors(mapFile, this, resources);
    LoadCeilings(mapFile, this, resources);
    LoadWalls(mapFile, this, resources);
    LoadEnemies(mapFile, this, resources);
    LoadSellers(mapFile, this, resources);

    fclose(mapFile);
}

void LoadSaveFile(struct SaveFile *this, struct Resources *resources) {
    CreateDate(this);

    LoadPlayer(this, resources);
    LoadShops(this);
    LoadMap(this, resources);
}