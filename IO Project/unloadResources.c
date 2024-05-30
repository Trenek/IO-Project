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

static void UnloadFonts(struct Resources *info) {
    int i = 0;

    while (i < info->fontsQuantity) {
        UnloadFont(info->fonts[i]);

        i += 1;
    }
    free(info->fonts);
}

static void unloadMusic(struct Resources *info) {
    int i = 0;

    while (i < info->musicQuantity) {
        UnloadMusicStream(info->music[i]);
        i += 1;
    }

    CloseAudioDevice();
    free(info->music);
}

static void unloadBodyPart(int num, struct Resources *info) {
    int i = 0;
    int j = 0;

    while (i < info->bodyPartsQuantity[num]) {
        j = 0;
        while (j < 4) {
            UnloadTexture(info->bodyParts[num][i][j]);

            j += 1;
        }

        i += 1;
    }

    free(info->bodyParts[num]);
}

static void unloadBodyParts(struct Resources *info) {
    int i = 0;

    while (i < 10) {
        unloadBodyPart(i, info);

        i += 1;
    }
}

static void unloadArmorPart(int num, struct Resources *info) {
    const char *directory = TextFormat("resources\\textures\\przedmioty\\armor\\%s", armorNames[num]);
    FilePathList files = LoadDirectoryFiles(directory);
    unsigned int i = 0;
    unsigned int j = 0;

    while (i < files.capacity) {
        j = 0;
        while (j < 4) {
            UnloadTexture(info->armorPart[num][i][j]);

            j += 1;
        }

        i += 1;
    }

    UnloadDirectoryFiles(files);
    free(info->armorPart[num]);
}

static void unloadArmor(struct Resources *info) {
    int i = 0;

    while (i < 9) {
        unloadArmorPart(i, info);

        i += 1;
    }
}

static void unloadArmorPrice(struct Resources *info) {
    int i = 0;

    for (i = 0; i < 9; i += 1) {
        free(info->armorPrice[i]);
        info->armorPrice[i] = NULL;
    }
}

static void unloadWeapons(struct Resources *info) {
    int i = 0;

    while (i < info->weaponsQuantity) {
        UnloadTexture(info->weapons[i]);

        i += 1;
    }

    free(info->weapons);
}

static void unloadWeaponPrice(struct Resources *info) {
    free(info->weaponPrice);
}

static void unloadItems(struct Resources *info) {
    int i = 0;

    while (i < info->itemsQuantity) {
        UnloadTexture(info->items[i]);

        i += 1;
    }

    free(info->items);
}

static void unloadItemPrice(struct Resources *info) {
    free(info->itemsPrice);
}

static void unloadFloors(struct Resources *info) {
    int i = 0;

    while (i < info->floorTextureQuantity) {
        UnloadTexture(info->floorTextures[i]);

        i += 1;
    }

    free(info->floorTextures);
}

static void unloadWalls(struct Resources *info) {
    int i = 0;

    while (i < info->wallTextureQuantity) {
        UnloadTexture(info->wallTextures[i]);

        i += 1;
    }

    free(info->wallTextures);
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