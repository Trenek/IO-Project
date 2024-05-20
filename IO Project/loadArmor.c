#include <malloc.h>
#include <stdio.h>

#include "playState.h"

static const char *const armorNames[] = {
    [HELMET] = "helmet",
    [BREASTPLATE] = "breastplate",
    [PANTS] = "pants",
    [LEFT_BOOT] = "left boot",
    [RIGHT_BOOT] = "right boot",
    [LEFT_GLOVE] = "left glove",
    [RIGHT_GLOVE] = "right glove",
    [LEFT_SLEEVE] = "left sleeve",
    [RIGHT_SLEEVE] = "right sleeve"
};

static void loadArmorPart(int num, struct playInfo *info) {
    const char *const directory = TextFormat("resources\\textures\\armor\\%s", armorNames[num]);
    char buffor[128];
    FilePathList files = LoadDirectoryFiles(directory);
    unsigned int i = 0;
    unsigned int j = 0;

    info->armorPart[num] = malloc(sizeof(Texture2D[4]) * files.capacity);

    while (i < files.capacity) {
        j = 0;
        while (j < 4) {
            sprintf(buffor, "%s\\%i\\%i\\0.png", directory, i, j);
            info->armorPart[num][i][j] = LoadTexture(buffor);
            j += 1;
        }

        i += 1;
    }

    UnloadDirectoryFiles(files);
}

static void unloadArmorPart(int num, struct playInfo *info) {
    const char *directory = TextFormat("resources\\textures\\armor\\%s", armorNames[num]);
    FilePathList files = LoadDirectoryFiles(directory);
    unsigned int i = 0;
    unsigned int j = 0;

    while (i < files.capacity) {
        j = 0;
        while (j < 4) {
            UnloadTexture(info->armorPart[num][i][j]);

            j += 1;
        }

        i += 1;
    }

    UnloadDirectoryFiles(files);
    free(info->armorPart[num]);
}

void loadArmor(struct playInfo *info) {
    int i = 0;

    while (i < 9) {
        loadArmorPart(i, info);

        i += 1;
    }
}

void unloadArmor(struct playInfo *info) {
    int i = 0;

    while (i < 9) {
        unloadArmorPart(i, info);

        i += 1;
    }
}