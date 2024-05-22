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

static void unloadShops(struct playInfo *info) {
    int i = 0;

    while (i < info->shopsQuantity) {
        unloadCharacter(&info->shops[i]);

        i += 1;
    }

    free(info->shops);
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

void unloadSaveFile(struct playInfo *this) {
    destroyEnemies(this);
    unloadShops(this);

    unloadPlayer(this);
}