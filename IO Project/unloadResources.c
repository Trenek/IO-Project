#include <stdlib.h>

#include "resources.h"

static void UnloadFonts(struct Resources *this) {
    int i = 0;

    while (i < this->fontsQuantity) {
        UnloadFont(this->fonts[i]);

        i += 1;
    }
    free(this->fonts);
}

static void UnloadMusic(struct Resources *this) {
    int i = 0;

    while (i < this->musicQuantity) {
        UnloadMusicStream(this->music[i]);
        i += 1;
    }

    CloseAudioDevice();
    free(this->music);
}

static void unloadBodyPart(int num, struct Resources *this) {
    int i = 0;
    int j = 0;

    while (i < this->bodyPartsQuantity[num]) {
        j = 0;
        while (j < 4) {
            UnloadTexture(this->bodyParts[num][i][j]);

            j += 1;
        }

        i += 1;
    }

    free(this->bodyParts[num]);
}

static void UnloadBodyParts(struct Resources *this) {
    int i = 0;

    while (i < 10) {
        unloadBodyPart(i, this);

        i += 1;
    }
}

static void unloadArmorPart(int num, struct Resources *this) {
    int i = 0;
    int j = 0;

    while (i < this->armorPartsQuantity[num]) {
        j = 0;
        while (j < 4) {
            UnloadTexture(this->armorPart[num][i][j]);

            j += 1;
        }

        i += 1;
    }

    free(this->armorPart[num]);
}

static void UnloadArmor(struct Resources *this) {
    int i = 0;

    while (i < 9) {
        unloadArmorPart(i, this);

        i += 1;
    }
}

static void UnloadArmorPrice(struct Resources *this) {
    int i = 0;

    for (i = 0; i < 9; i += 1) {
        free(this->armorPrice[i]);
        this->armorPrice[i] = NULL;
    }
}

static void UnloadWeapons(struct Resources *this) {
    int i = 0;

    while (i < this->weaponsQuantity) {
        UnloadTexture(this->weapons[i]);

        i += 1;
    }

    free(this->weapons);
}

static void UnloadWeaponPrice(struct Resources *this) {
    free(this->weaponPrice);
}

static void UnloadItems(struct Resources *this) {
    int i = 0;

    while (i < this->itemsQuantity) {
        UnloadTexture(this->items[i]);

        i += 1;
    }

    free(this->items);
}

static void UnloadItemPrice(struct Resources *this) {
    free(this->itemsPrice);
}

static void UnloadFloors(struct Resources *this) {
    int i = 0;

    while (i < this->floorQuantity) {
        UnloadTexture(this->floors[i]);

        i += 1;
    }

    free(this->floors);
}

static void UnloadCeilings(struct Resources *this) {
    int i = 0;

    while (i < this->ceilingQuantity) {
        UnloadTexture(this->ceiling[i]);

        i += 1;
    }

    free(this->ceiling);
}

static void UnloadWalls(struct Resources *this) {
    int i = 0;

    while (i < this->wallQuantity) {
        UnloadTexture(this->walls[i]);

        i += 1;
    }

    free(this->walls);
}

void UnloadResources(struct Resources *this) {
    UnloadFonts(this);
    UnloadMusic(this);

    UnloadBodyParts(this);

    UnloadArmor(this);
    UnloadArmorPrice(this);

    UnloadWeapons(this);
    UnloadWeaponPrice(this);
    UnloadItems(this);
    UnloadItemPrice(this);
    UnloadFloors(this);
    UnloadCeilings(this);
    UnloadWalls(this);
}