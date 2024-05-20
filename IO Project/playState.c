#include <stdlib.h>
#include <raylib.h>

#include <stdio.h>

#include "state.h"
#include "playState.h"

#include "character.h"
#include "object2D.h"
#include "player.h"

static const char * const bodyPartsNames[] = {
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

static void loadBodyPart(int num, struct playInfo *info) {
    const char * const directory = TextFormat("resources\\textures\\body\\%s", bodyPartsNames[num]);
    char buffor[128];
    FilePathList files = LoadDirectoryFiles(directory);
    unsigned int i = 0;
    unsigned int j = 0;

    info->bodyParts[num] = malloc(sizeof(Texture2D [4]) * files.capacity);
    
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

static void unloadBodyPart(int num, struct playInfo *info) {
    const char *directory = TextFormat("resources\\textures\\body\\%s", bodyPartsNames[num]);
    FilePathList files = LoadDirectoryFiles(directory);
    unsigned int i = 0;
    unsigned int j = 0;

    while (i < files.capacity) {
        j = 0;
        while (j < 4) {
            UnloadTexture(info->bodyParts[num][i][j]);

            j += 1;
        }

        i += 1;
    }

    UnloadDirectoryFiles(files);
    free(info->bodyParts[num]);
}


static void loadBodyParts(struct playInfo *info) {
    int i = 0;

    while (i <= RIGHT_FOOT) {
        loadBodyPart(i, info);

        i += 1;
    }
}

static void unloadBodyParts(struct playInfo *info) {
    int i = 0;

    while (i <= RIGHT_FOOT) {
        unloadBodyPart(i, info);

        i += 1;
    }
}

static void setBodyPosition(struct playInfo *info) {
    FILE *bodyType = fopen("dane\\bodyType.txt", "r");
    int i = 0;
    int j = 0;

    fscanf(bodyType, "%i %i", &info->width, &info->height);

    while (i < 4) {
        j = 0;
        while (j < 10) {
            fscanf(bodyType, "%i %i", &info->bodyPosition[i][j][0], &info->bodyPosition[i][j][1]);

            j += 1;
        }

        i += 1;
    }

    fclose(bodyType);
}

static void loadPlayer(struct playInfo *info, const char* saveName) {
    loadCharacter(&info->player.character, TextFormat("saves\\%s\\postaæ.txt", saveName), 4.0f, 0.0f);
    assemblePlayerTexture(info, &info->player.character);

    info->player.speedY = 0;
}

static void unloadPlayer(struct playInfo *info) {
    unloadCharacter(&info->player.character);
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
  
    setBodyPosition(&result);

    loadBodyParts(&result);

    createEnemies(mapFile, &result);
    loadShops(mapFile, &result);

    loadPlayer(&result, info->saveName);

    fclose(mapFile);

    return result;
}

void freePlayInfo(struct playInfo *info) {
    UnloadRenderTexture(*info->screenCamera);

    unloadPlayer(info);

    destroyEnemies(info);
    unloadShops(info);

    unloadBodyParts(info);

    free(info->screenCamera);
    free(info->screenRect);
}