#include <stdlib.h>
#include <raylib.h>

#include <stdio.h>

#include "state.h"
#include "playState.h"

#include "character.h"
#include "object2D.h"
#include "player.h"

#include "load.h"

static void loadBodyPosition(struct playInfo *info) {
    FILE *bodyMeasurements = fopen("dane\\bodyMeasurements.txt", "r");
    int i = 0;
    int j = 0;

    fscanf(bodyMeasurements, "%i %i", &info->width, &info->height);

    while (i < 4) {
        j = 0;
        while (j < 10) {
            fscanf(bodyMeasurements, "%i %i", &info->bodyPosition[i][j][0], &info->bodyPosition[i][j][1]);

            j += 1;
        }

        i += 1;
    }

    fclose(bodyMeasurements);
}

static void loadArmorPosition(struct playInfo *info) {
    FILE *armorMeasurements = fopen("dane\\armorMeasurements.txt", "r");
    int i = 0;
    int j = 0;

    while (i < 4) {
        j = 0;
        while (j < 9) {
            fscanf(armorMeasurements, "%i %i", &info->armorPosition[i][j][0], &info->armorPosition[i][j][1]);

            j += 1;
        }

        i += 1;
    }

    fclose(armorMeasurements);
}

static void createEnemies(FILE* file, struct playInfo *info) {
    int i = 0;
    int id = 0;
    float x = 0.0f;
    float y = 0.0f;

    fscanf(file, "%i", &info->enemyQuantity);
    info->enemies = malloc(sizeof(struct character) * info->enemyQuantity);

    while (i < info->enemyQuantity) {
        fscanf(file, "%i %i %f %f", &id, &info->enemies[i].dialog, &x, &y);

        loadCharacter(&info->enemies[i], TextFormat("dane\\postacie\\%i.txt", id), x, y);
        assemblePlayerTexture(info, &info->enemies[i]);

        i += 1;
    }
}

static void destroyEnemies(struct playInfo *info) {
    int i = 0;

    while (i < info->enemyQuantity) {
        unloadCharacter(&info->enemies[i]);

        i += 1;
    }

    free(info->enemies);
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

        loadCharacter(&info->shops[i], TextFormat("dane\\postacie\\%i.txt", id), x, y);
        assemblePlayerTexture(info, &info->shops[i]);

        i += 1;
    }
}

static void unloadShops(struct playInfo *info) {
    int i = 0;

    while (i < info->shopsQuantity) {
        unloadCharacter(&info->shops[i]);

        i += 1;
    }

    free(info->shops);
}

static void loadWeapons(struct playInfo *info) {
    FilePathList files = LoadDirectoryFiles("resources\\textures\\weapon");
    int i = 0;

    info->weaponsQuantity = files.capacity;

    info->weapons = malloc(sizeof(Texture2D) * info->weaponsQuantity);
    while (i < info->weaponsQuantity) {
        info->weapons[i] = LoadTexture(TextFormat("resources\\textures\\weapon\\%i.png", i));

        i += 1;
    }

    UnloadDirectoryFiles(files);
}

static void unloadWeapons(struct playInfo *info) {
    int i = 0;

    while (i < info->weaponsQuantity) {
        UnloadTexture(info->weapons[i]);

        i += 1;
    }

    free(info->weapons);
}

static void loadItems(struct playInfo *info) {
    FilePathList files = LoadDirectoryFiles("resources\\textures\\przedmioty");
    int i = 0;

    info->itemsQuantity = files.capacity;

    info->items = malloc(sizeof(Texture2D) * info->itemsQuantity);
    while (i < info->itemsQuantity) {
        info->items[i] = LoadTexture(TextFormat("resources\\textures\\przedmioty\\%i.png", i));

        i += 1;
    }

    UnloadDirectoryFiles(files);
}

static void unloadItems(struct playInfo *info) {
    int i = 0;

    while (i < info->itemsQuantity) {
        UnloadTexture(info->items[i]);

        i += 1;
    }

    free(info->items);
}

struct playInfo initializePlayInfo(struct menuInfo *info) {
    struct playInfo result = {
        .fonts = info->fonts,
        .fontsQuantity = info->fontsQuantity,
        .music = info->music,
        .musicQuantity = info->musicQuantity,
        .screenCamera = malloc(sizeof(RenderTexture)),
        .screenRect = malloc(sizeof(Rectangle)),
        .camera = {
            .position = {
                .x = 10,
                .y = 2,
                .z = 0
            },
            .up.y = 1,
            .fovy = 45
        }
    };
    FILE *mapFile = fopen(TextFormat("saves\\%s\\mapy\\0.txt", info->saveName), "r");

    *result.screenCamera = LoadRenderTexture(GetScreenWidth(), GetScreenHeight() + 20);
    *result.screenRect = (Rectangle){ 0.0f, 0.0f, (float)result.screenCamera->texture.width, (float)-result.screenCamera->texture.height };

    loadBodyPosition(&result);
    loadArmorPosition(&result);

    loadBodyParts(&result);
    loadArmor(&result);

    createEnemies(mapFile, &result);
    loadShops(mapFile, &result);

    loadItems(&result);
    loadWeapons(&result);

    loadPlayer(&result, info->saveName);

    fclose(mapFile);

    return result;
}

void freePlayInfo(struct playInfo *info) {
    UnloadRenderTexture(*info->screenCamera);

    unloadPlayer(info);

    unloadItems(info);
    unloadWeapons(info);

    destroyEnemies(info);
    unloadShops(info);

    unloadArmor(info);
    unloadBodyParts(info);

    free(info->screenCamera);
    free(info->screenRect);
}