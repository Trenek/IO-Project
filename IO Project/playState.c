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


static void loadTextures(struct playInfo *info) {
    int i = 0;
    Texture2D characters[] = {
        LoadTexture("resources/textures/pixel/WarriorFront0.png"),
        LoadTexture("resources/textures/ludzik2.png"),
        LoadTexture("resources/textures/mag.png"),
        LoadTexture("resources/textures/arystokrata2.png")
    };

    info->texturesQuantity = sizeof(characters) / sizeof(Texture2D);
    info->textures = malloc(sizeof(characters));

    while (i < info->texturesQuantity) {
        info->textures[i] = characters[i];

        i += 1;
    }
}

static void unloadTextures(struct playInfo *info) {
    int i = 0;

    while (i < info->texturesQuantity) {
        UnloadTexture(info->textures[i]);

        i += 1;
    }
    free(info->textures);
}

struct Object2D createObject(int x, int z, Texture2D *texture) {
    return (struct Object2D) {
        .position = { 
            .x = (float)x, 
            .y = 0.0f,
            .z = (float)z 
        },
        .sizeV = {
            .x = texture->width / (0.5f * texture->height),
            .y = texture->height / (0.5f * texture->height)
        },
        .texture = texture
    };
}

static void createObjects(struct playInfo *info) {
    struct Object2D objects[4] = {
        createObject(4, 0, &info->textures[0]),
        createObject(-4, 0, &info->textures[1]),
        createObject(0, 4, &info->textures[2]),
        createObject(0, -4, &info->textures[3])
    };
    int i = 0;

    info->objectsQuantity = sizeof(objects) / sizeof(struct Object2D);
    info->objects = malloc(sizeof(objects));
      
    while (i < info->objectsQuantity) {
        info->objects[i] = objects[i];

        i += 1;
    }
}

static void destroyObjects(struct playInfo *info) {
    free(info->objects);
}

static void createNPCs(struct playInfo *info) {
    int i = 1;

    info->npc = malloc(sizeof(struct character) * (info->objectsQuantity));
    while (i < info->objectsQuantity) {
        if (i != 0) info->npc[i - 1].object = info->objects[i];

        i += 1;
    }
}

static void destroyNPCs(struct playInfo *info) {
    free(info->npc);
}

static void loadBodyPart(int num, struct playInfo *info) {
    const char * const directory = TextFormat("resources\\textures\\body\\%s", bodyPartsNames[num]);
    char buffor[128];
    FilePathList files = LoadDirectoryFiles(directory);
    unsigned int i = 0;
    unsigned int j = 0;

    info->texturePosition[num] = malloc(sizeof(struct TexturePosition) * files.capacity);
    
    while (i < files.capacity) {
        j = 0;
        while (j < 4) {
            sprintf(buffor, "%s\\%i\\%i\\0.png", directory, i, j);
            info->texturePosition[num][i].position[j] = LoadTexture(buffor);
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
            UnloadTexture(info->texturePosition[num][i].position[j]);

            j += 1;
        }

        i += 1;
    }

    free(info->texturePosition[num]);
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
    FILE *player = fopen(TextFormat("saves\\%s\\postaæ.txt", saveName), "r");
    struct character *character = &info->player.character;
    struct Object2D *object = &character->object;
    int i = 0;

    float x = 0;
    float y = 0;

    character->direction = 0;

    fscanf(player, "%s", character->name);
    fscanf(player, "%f %f", &x, &y);

    object->sizeV.x = x;
    object->sizeV.y = y;

    i = 0;
    while (i < 10) {
        fscanf(player, "%i", &character->bodyPart[i]);
           
        i += 1;
    }

    info->player.character.object.texture = malloc(sizeof(Texture2D));
    assemblePlayerTexture(info, &info->player.character);

    info->player.speedY = 0;

    fclose(player);
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

    loadTextures(&result);
    loadBodyParts(&result);

    createObjects(&result);
    createNPCs(&result);

    loadPlayer(&result, info->saveName);

    return result;
}

void freePlayInfo(struct playInfo *info) {
    UnloadRenderTexture(*info->screenCamera);

    unloadTextures(info);
    unloadBodyParts(info);

    destroyObjects(info);
    destroyNPCs(info);

    free(info->screenCamera);
    free(info->screenRect);
}