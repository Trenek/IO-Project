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

static void loadShops(FILE *file, struct playInfo *info) {
    int i = 0;
    int id = 0;
    float x = 0.0f;
    float y = 0.0f;

    fscanf(file, "%i", &info->shopsQuantity);
    info->shops = malloc(sizeof(struct character) * info->shopsQuantity);

    while (i < info->shopsQuantity) {
        fscanf(file, "%i %i %f %f", &id, &info->shops[i].dialog, &x, &y);

        info->shops[i].ID = id;
        loadCharacter(&info->shops[i], TextFormat("dane\\postacie\\%i.txt", id), x, y);
        assemblePlayerTexture(info, &info->shops[i]);

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

            if (player->equipment[i][1] == 2) {
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

    createEnemies(mapFile, this);
    loadShops(mapFile, this);

    loadPlayer(this, saveName);

    fclose(mapFile);
}