#include <stdlib.h>
#include <raylib.h>

#include <stdio.h>

#include "state.h"
#include "playState.h"

#include "character.h"
#include "object2D.h"
#include "player.h"

static const char *bodyPartsNames[] = {
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
    loadCharacter(&info->player.character, TextFormat("saves\\%s\\posta�.txt", saveName), 4.0f, 0.0f);
    assemblePlayerTexture(info, &info->player.character);

    info->player.speedY = 0;
}

static void unloadPlayer(struct playInfo *info) {
    unloadCharacter(&info->player.character);
}

static void createNPCs(struct playInfo *info) {
    int i = 0;

    info->npcQuantity = 3;
    info->npc = malloc(sizeof(struct character) * info->npcQuantity);

    loadCharacter(&info->npc[0], "dane\\postacie\\0.txt", -4.0f, 0.0f);
    loadCharacter(&info->npc[1], "dane\\postacie\\0.txt", 0.0f, 4.0f);
    loadCharacter(&info->npc[2], "dane\\postacie\\0.txt", 0.0f, -4.0f);

    while (i < info->npcQuantity) {
        assemblePlayerTexture(info, &info->npc[i]);

        i += 1;
    }
}

static void destroyNPCs(struct playInfo *info) {
    int i = 0;

    while (i < info->npcQuantity) {
        unloadCharacter(&info->npc[i]);

        i += 1;
    }

    free(info->npc);
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

    *result.screenCamera = LoadRenderTexture(GetScreenWidth(), GetScreenHeight() + 20);
    *result.screenRect = (Rectangle){ 0.0f, 0.0f, (float)result.screenCamera->texture.width, (float)-result.screenCamera->texture.height };
  
    setBodyPosition(&result);

    loadBodyParts(&result);

    createNPCs(&result);
    loadPlayer(&result, info->saveName);

    return result;
}

void freePlayInfo(struct playInfo *info) {
    UnloadRenderTexture(*info->screenCamera);

    unloadPlayer(info);
    destroyNPCs(info);

    unloadBodyParts(info);

    free(info->screenCamera);
    free(info->screenRect);
}