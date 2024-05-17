#include <stdlib.h>
#include <raylib.h>

#include "state.h"
#include "playState.h"

#include "character.h"
#include "object2D.h"
#include "player.h"

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
        .texture = texture,
        .Animation = NULL,
        .animFrame = 0,
        .state = 0
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
    
    loadTextures(&result);

    createObjects(&result);
    createNPCs(&result);
    result.player = (struct player){
        .character.object = *result.objects,
        .speedY = 0
    };


    return result;
}

void freePlayInfo(struct playInfo *info) {
    UnloadRenderTexture(*info->screenCamera);

    unloadTextures(info);

    destroyObjects(info);
    destroyNPCs(info);

    free(info->screenCamera);
    free(info->screenRect);
}