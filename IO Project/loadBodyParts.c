#include <malloc.h>
#include <stdio.h>

#include "playState.h"

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

static void loadBodyPart(int num, Texture2D(*bodyParts[10])[4]) {
    const char *const directory = TextFormat("resources\\textures\\body\\%s", bodyPartsNames[num]);
    char buffor[128];
    FilePathList files = LoadDirectoryFiles(directory);
    unsigned int i = 0;
    unsigned int j = 0;

    bodyParts[num] = malloc(sizeof(Texture2D[4]) * files.capacity);

    while (i < files.capacity) {
        j = 0;
        while (j < 4) {
            sprintf(buffor, "%s\\%i\\%i\\0.png", directory, i, j);
            bodyParts[num][i][j] = LoadTexture(buffor);
            j += 1;
        }

        i += 1;
    }

    UnloadDirectoryFiles(files);
}

static void unloadBodyPart(int num, Texture2D(*bodyParts[10])[4]) {
    const char *directory = TextFormat("resources\\textures\\body\\%s", bodyPartsNames[num]);
    FilePathList files = LoadDirectoryFiles(directory);
    unsigned int i = 0;
    unsigned int j = 0;

    while (i < files.capacity) {
        j = 0;
        while (j < 4) {
            UnloadTexture(bodyParts[num][i][j]);

            j += 1;
        }

        i += 1;
    }

    UnloadDirectoryFiles(files);
    free(bodyParts[num]);
}


void loadBodyParts(Texture2D(*bodyParts[10])[4]) {
    int i = 0;

    while (i < 10) {
        loadBodyPart(i, bodyParts);

        i += 1;
    }
}

void unloadBodyParts(Texture2D(*bodyParts[10])[4]) {
    int i = 0;

    while (i < 10) {
        unloadBodyPart(i, bodyParts);

        i += 1;
    }
}