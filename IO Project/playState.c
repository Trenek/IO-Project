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

void loadBodyPosition(struct playInfo *info) {
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

void loadArmorPosition(struct playInfo *info) {
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

void loadArmorPrice(struct playInfo *info) {
    FILE *file = fopen("dane\\przedmioty\\armor.txt", "r");
    int i = 0;
    int j = 0;
    int quantity = 0;

    while (i < 9) {
        fscanf(file, "%i", &quantity);
        info->armorPrice[i] = malloc(sizeof(int[3]) * quantity);

        j = 0;
        while (j < quantity) {
            fscanf(file, "%i", &info->armorPrice[i][j][0]);

            if (info->armorPrice[i][j][0] != 0) {
                fscanf(file, "%i", &info->armorPrice[i][j][1]);

                if (info->armorPrice[i][j][0] == 2) {
                    fscanf(file, "%i", &info->armorPrice[i][j][2]);
                }
            }

            j += 1;
        }

        i += 1;
    }

    fclose(file);
}

void unloadArmorPrice(struct playInfo *info) {
    int i = 0;

    for (i = 0; i < 9; i += 1) {
        free(info->armorPrice[i]);
        info->armorPrice[i] = NULL;
    }
}

void loadWeaponPrice(struct playInfo *info) {
    FILE *file = fopen("dane\\przedmioty\\weapon.txt", "r");
    int j = 0;
    int quantity = 0;

    fscanf(file, "%i", &quantity);
    info->weaponPrice = malloc(sizeof(int[3]) * quantity);

    j = 0;
    while (j < quantity) {
        fscanf(file, "%i", &info->weaponPrice[j][0]);

        if (info->weaponPrice[j][0] != 0) {
            fscanf(file, "%i", &info->weaponPrice[j][1]);

            if (info->weaponPrice[j][0] == 2) {
                fscanf(file, "%i", &info->weaponPrice[j][2]);
            }
        }

        j += 1;
    }

    fclose(file);
}

void unloadWeaponPrice(struct playInfo *info) {
    free(info->weaponPrice);
}

void loadItemPrice(struct playInfo *info) {
    FILE *file = fopen("dane\\przedmioty\\inne.txt", "r");
    int j = 0;
    int quantity = 0;

    fscanf(file, "%i", &quantity);
    info->itemsPrice = malloc(sizeof(int[3]) * quantity);

    j = 0;
    while (j < quantity) {
        fscanf(file, "%i", &info->itemsPrice[j][0]);

        if (info->itemsPrice[j][0] != 0) {
            fscanf(file, "%i", &info->itemsPrice[j][1]);

            if (info->itemsPrice[j][0] == 2) {
                fscanf(file, "%i", &info->itemsPrice[j][2]);
            }
        }

        j += 1;
    }

    fclose(file);
}

void unloadItemPrice(struct playInfo *info) {
    free(info->itemsPrice);
}

static void loadWeapons(struct playInfo *info) {
    FilePathList files = LoadDirectoryFiles("resources\\textures\\przedmioty\\weapon");
    int i = 0;

    info->weaponsQuantity = files.capacity;

    info->weapons = malloc(sizeof(Texture2D) * info->weaponsQuantity);
    while (i < info->weaponsQuantity) {
        info->weapons[i] = LoadTexture(TextFormat("resources\\textures\\przedmioty\\weapon\\%i.png", i));

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
    FilePathList files = LoadDirectoryFiles("resources\\textures\\przedmioty\\inne");
    int i = 0;

    info->itemsQuantity = files.capacity;

    info->items = malloc(sizeof(Texture2D) * info->itemsQuantity);
    while (i < info->itemsQuantity) {
        info->items[i] = LoadTexture(TextFormat("resources\\textures\\przedmioty\\inne\\%i.png", i));

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

    loadArmorPrice(&result);
    loadWeaponPrice(&result);
    loadItemPrice(&result);

    loadBodyParts(&result);
    loadArmor(&result);

    loadSaveFile(&result, info->saveName);

    loadItems(&result);
    loadWeapons(&result);

    return result;
}

void freePlayInfo(struct playInfo *info) {
    unloadWeapons(info);
    unloadItems(info);

    unloadSaveFile(info);

    unloadArmor(info);
    unloadBodyParts(info);

    unloadItemPrice(info);
    unloadWeaponPrice(info);
    unloadArmorPrice(info);

    UnloadRenderTexture(*info->screenCamera);

    free(info->screenCamera);
    free(info->screenRect);
}