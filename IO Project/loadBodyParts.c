#include <malloc.h>
#include <stdio.h>

#include "state.h"
#include "bodyParts.h"

static const char *const bodyPartsNames[] = {
    [HEAD] = "head",
    [TORSO] = "torso",
    [LEFT_ARM] = "left arm",
    [RIGHT_ARM] = "right arm",
    [LEFT_HAND] = "left hand",
    [RIGHT_HAND] = "right hand",
    [LEFT_LEG] = "left leg",
    [RIGHT_LEG] = "right leg",
    [LEFT_FOOT] = "left foot",
    [RIGHT_FOOT] = "right foot"
};

void loadBodyPosition(struct menuInfo *info) {
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

static void loadBodyPart(int num, struct menuInfo *info) {
    const char *const directory = TextFormat("resources\\textures\\body\\%s", bodyPartsNames[num]);
    char buffor[128];
    FilePathList files = LoadDirectoryFiles(directory);
    unsigned int i = 0;
    unsigned int j = 0;

    info->bodyPartsQuantity[num] = files.capacity;
    info->bodyParts[num] = malloc(sizeof(Texture2D[4]) * files.capacity);

    while (i < files.capacity) {
        j = 0;
        while (j < 4) {
            sprintf(buffor, "%s\\%i\\%i\\0.png", directory, i, j);
            info->bodyParts[num][i][j] = LoadTexture(buffor);
            j += 1;
        }

        i += 1;
    }

    UnloadDirectoryFiles(files);
}

static void unloadBodyPart(int num, struct menuInfo *info) {
    int i = 0;
    int j = 0;

    while (i < info->bodyPartsQuantity[num]) {
        j = 0;
        while (j < 4) {
            UnloadTexture(info->bodyParts[num][i][j]);

            j += 1;
        }

        i += 1;
    }

    free(info->bodyParts[num]);
}

void loadBodyParts(struct menuInfo *info) {
    int i = 0;

    while (i < 10) {
        loadBodyPart(i, info);

        i += 1;
    }
}

void unloadBodyParts(struct menuInfo *info) {
    int i = 0;

    while (i < 10) {
        unloadBodyPart(i, info);

        i += 1;
    }
}