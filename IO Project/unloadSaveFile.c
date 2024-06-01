#include <stdlib.h>

#include "savefile.h"

void UnloadCharacter(struct character *character) {
    if (character->object.texture != NULL) {
        UnloadTexture(*character->object.texture);

        free(character->object.texture);
    }
}

static void UnloadPlayer(struct SaveFile *this) {
    UnloadCharacter(&this->player.character);
}

static void UnloadShops(struct SaveFile *this) {
    free(this->shopEquipment);
}

static void UnloadFloors(struct SaveFile *this) {
    free(this->floors);
}

static void UnloadCeilings(struct SaveFile *this) {
    free(this->ceiling);
}

static void UnloadWalls(struct SaveFile *this) {
    free(this->walls);
}

static void UnloadEnemies(struct SaveFile *this) {
    int i = 0;

    while (i < this->enemyQuantity) {
        UnloadCharacter(&this->enemies[i]);

        i += 1;
    }

    free(this->enemies);
}

static void UnloadSellers(struct SaveFile *this) {
    int i = 0;

    while (i < this->sellersQuantity) {
        UnloadCharacter(&this->sellers[i].character);

        i += 1;
    }

    free(this->sellers);
}

static void UnloadMap(struct SaveFile *this) {
    UnloadFloors(this);
    UnloadCeilings(this);
    UnloadWalls(this);
    UnloadEnemies(this);
    UnloadSellers(this);
}

void UnloadSaveFile(struct SaveFile *this) {
    UnloadPlayer(this);

    UnloadShops(this);

    UnloadMap(this);
}