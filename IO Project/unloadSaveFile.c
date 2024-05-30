#include <stdio.h>
#include <stdlib.h>

#include "savefile.h"
#include "playState.h"

#include "player.h"

static void destroyEnemies(struct playInfo *info) {
    int i = 0;

    while (i < info->enemyQuantity) {
        unloadCharacter(&info->enemies[i]);

        i += 1;
    }

    free(info->enemies);
}

static void unloadSellers(struct playInfo *info) {
    int i = 0;

    while (i < info->sellersQuantity) {
        unloadCharacter(&info->shops[i].character);

        i += 1;
    }

    free(info->shops);
}

static void unloadFloors(struct playInfo *info) {
    int i = 0;

    while (i < info->floorsQuantity) {
        UnloadTexture(*info->floors[i].object.texture);
        free(info->floors[i].object.texture);

        i += 1;
    }

    free(info->floors);
}

static void unloadWalls(struct playInfo *info) {
    int i = 0;

    while (i < info->wallQuantity) {
        UnloadTexture(*info->walls[i].object.texture);
        free(info->walls[i].object.texture);

        i += 1;
    }

    free(info->walls);
}

void unloadCharacter(struct character *character) {
    if (character->object.texture != NULL) {
        UnloadTexture(*character->object.texture);

        free(character->object.texture);
    }
}

static void unloadPlayer(struct playInfo *info) {
    unloadCharacter(&info->player.character);
}

static void unloadShops(struct playInfo *this) {
    free(this->shopEquipment);
}

void unloadSaveFile(struct playInfo *this) {
    destroyEnemies(this);
    unloadSellers(this);
    unloadShops(this);
    unloadFloors(this);
    unloadWalls(this);

    unloadPlayer(this);
}