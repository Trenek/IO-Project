#include <stdlib.h>

#include "resources.h"

static const char *const armorNames[] = {
    [HELMET] = "helmet",
    [BREASTPLATE] = "breastplate",
    [PANTS] = "pants",
    [LEFT_BOOT] = "left boot",
    [RIGHT_BOOT] = "right boot",
    [LEFT_GLOVE] = "left glove",
    [RIGHT_GLOVE] = "right glove",
    [LEFT_SLEEVE] = "left sleeve",
    [RIGHT_SLEEVE] = "right sleeve"
};

static void UnloadFonts(struct Resources *this) {
    int i = 0;

    while (i < this->fontsQuantity) {
        UnloadFont(this->fonts[i]);

        i += 1;
    }
    free(this->fonts);
}

static void unloadMusic(struct Resources *this) {
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

static void unloadBodyParts(struct Resources *this) {
    int i = 0;

    while (i < 10) {
        unloadBodyPart(i, this);

        i += 1;
    }
}

static void unloadArmorPart(int num, struct Resources *this) {
    const char *directory = TextFormat("resources\\textures\\przedmioty\\armor\\%s", armorNames[num]);
    FilePathList files = LoadDirectoryFiles(directory);
    unsigned int i = 0;
    unsigned int j = 0;

    while (i < files.capacity) {
        j = 0;
        while (j < 4) {
            UnloadTexture(this->armorPart[num][i][j]);

            j += 1;
        }

        i += 1;
    }

    UnloadDirectoryFiles(files);
    free(this->armorPart[num]);
}

static void unloadArmor(struct Resources *this) {
    int i = 0;

    while (i < 9) {
        unloadArmorPart(i, this);

        i += 1;
    }
}

static void unloadArmorPrice(struct Resources *this) {
    int i = 0;

    for (i = 0; i < 9; i += 1) {
        free(this->armorPrice[i]);
        this->armorPrice[i] = NULL;
    }
}

static void unloadWeapons(struct Resources *this) {
    int i = 0;

    while (i < this->weaponsQuantity) {
        UnloadTexture(this->weapons[i]);

        i += 1;
    }

    free(this->weapons);
}

static void unloadWeaponPrice(struct Resources *this) {
    free(this->weaponPrice);
}

static void unloadItems(struct Resources *this) {
    int i = 0;

    while (i < this->itemsQuantity) {
        UnloadTexture(this->items[i]);

        i += 1;
    }

    free(this->items);
}

static void unloadItemPrice(struct Resources *this) {
    free(this->itemsPrice);
}

static void unloadFloors(struct Resources *this) {
    int i = 0;

    while (i < this->floorTextureQuantity) {
        UnloadTexture(this->floorTextures[i]);

        i += 1;
    }

    free(this->floorTextures);
}

static void unloadWalls(struct Resources *this) {
    int i = 0;

    while (i < this->wallTextureQuantity) {
        UnloadTexture(this->wallTextures[i]);

        i += 1;
    }

    free(this->wallTextures);
}

void unloadResources(struct Resources *this) {
    UnloadFonts(this);
    unloadMusic(this);
    unloadBodyParts(this);
    unloadArmor(this);
    unloadArmorPrice(this);
    unloadWeapons(this);
    unloadWeaponPrice(this);
    unloadItems(this);
    unloadItemPrice(this);
    unloadFloors(this);
    unloadWalls(this);
}