#include <stdlib.h>
#include <raylib.h>

#include <stdio.h>

#include "state.h"
#include "playState.h"

#include "character.h"
#include "object2D.h"
#include "player.h"

#include "load.h"
#include "savefile.h"

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
        .saveName = info->saveName,
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

    *result.screenCamera = LoadRenderTexture(GetScreenWidth(), GetScreenHeight() + 20);
    *result.screenRect = (Rectangle){ 0.0f, 0.0f, (float)result.screenCamera->texture.width, (float)-result.screenCamera->texture.height };

    loadBodyPosition(&result);
    loadArmorPosition(&result);

    loadBodyParts(&result);
    loadArmor(&result);

    loadSaveFile(&result, info->saveName);

    loadItems(&result);
    loadWeapons(&result);

    return result;
}

void freePlayInfo(struct playInfo *info) {
    UnloadRenderTexture(*info->screenCamera);

    unloadItems(info);
    unloadWeapons(info);

    unloadSaveFile(info);

    unloadArmor(info);
    unloadBodyParts(info);

    free(info->screenCamera);
    free(info->screenRect);
}