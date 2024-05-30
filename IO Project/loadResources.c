#include <stdio.h>
#include <stdlib.h>

#include "resources.h"

static const char *const bodyPartsNames[] = {
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

static void SetFonts(struct Resources *info) {
    int letters[] = U"?!,._<>:()^/*a¹bcædeêfghijkl³mnñoópqrsœtuvwxyzŸ¿A¥BCÆDEÊFGHIJKL£MNÑOÓPQRSŒTUVWXYZ¯1234567890";
    Font fonts[] = {
        LoadFontEx("resources/fonts/font2.ttf", 100, letters, sizeof(letters) / sizeof(int)),
        LoadFontEx("resources/fonts/font5.ttf", 100, letters, sizeof(letters) / sizeof(int))
    };
    int i = 0;

    info->fontsQuantity = sizeof(fonts) / sizeof(Font);
    info->fonts = malloc(sizeof(fonts));

    while (i < info->fontsQuantity) {
        info->fonts[i] = fonts[i];
        GenTextureMipmaps(&info->fonts[i].texture);
        SetTextureFilter(info->fonts[i].texture, TEXTURE_FILTER_POINT);

        i += 1;
    }
}

static void loadMusic(struct Resources *info) {
    InitAudioDevice();

    Music music[] = {
        LoadMusicStream("resources/music/music1.mp3"),
        LoadMusicStream("resources/music/music2.mp3")
    };
    int i = 0;

    info->music = malloc(sizeof(music));
    info->musicQuantity = sizeof(music) / sizeof(Music);
    while (i < info->musicQuantity) {
        info->music[i] = music[i];
        i += 1;
    }

    i = 0;
    while (i < info->musicQuantity) {
        PlayMusicStream(info->music[i]);
        i += 1;
    }
}

static void loadBodyPosition(struct Resources *info) {
    FILE *bodyMeasurements = fopen("dane\\bodyMeasurements.txt", "r");
    int i = 0;
    int j = 0;

    fscanf(bodyMeasurements, "%i %i", &info->width, &info->height);

    while (i < 4) {
        j = 0;
        while (j < 10) {
            fscanf(bodyMeasurements, "%i %i", &info->bodyPosition[i][j][0], &info->bodyPosition[i][j][1]);

            j += 1;
        }

        i += 1;
    }

    fclose(bodyMeasurements);
}

static void loadBodyPart(int num, struct Resources *info) {
    const char *const directory = TextFormat("resources\\textures\\body\\%s", bodyPartsNames[num]);
    char buffor[128];
    FilePathList files = LoadDirectoryFiles(directory);
    unsigned int i = 0;
    unsigned int j = 0;

    info->bodyPartsQuantity[num] = files.capacity;
    info->bodyParts[num] = malloc(sizeof(Texture2D[4]) * files.capacity);

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

static void loadBodyParts(struct Resources *info) {
    int i = 0;

    while (i < 10) {
        loadBodyPart(i, info);

        i += 1;
    }
}

static void loadArmorPart(int num, struct Resources *info) {
    const char *const directory = TextFormat("resources\\textures\\przedmioty\\armor\\%s", armorNames[num]);
    char buffor[128];
    FilePathList files = LoadDirectoryFiles(directory);
    unsigned int i = 0;
    unsigned int j = 0;

    info->armorPart[num] = malloc(sizeof(Texture2D[4]) * files.capacity);

    while (i < files.capacity) {
        j = 0;
        while (j < 4) {
            sprintf(buffor, "%s\\%i\\%i\\0.png", directory, i, j);
            info->armorPart[num][i][j] = LoadTexture(buffor);
            j += 1;
        }

        i += 1;
    }

    UnloadDirectoryFiles(files);
}

static void loadArmor(struct Resources *info) {
    int i = 0;

    while (i < 9) {
        loadArmorPart(i, info);

        i += 1;
    }
}

static void loadArmorPrice(struct Resources *info) {
    FILE *file = fopen("dane\\przedmioty\\armor.txt", "r");
    int i = 0;
    int j = 0;
    int quantity = 0;

    while (i < 9) {
        fscanf(file, "%i", &quantity);
        info->armorPrice[i] = malloc(sizeof(int[3]) * quantity);

        j = 0;
        while (j < quantity) {
            fscanf(file, "%i", &info->armorPrice[i][j][0]);

            if (info->armorPrice[i][j][0] != 0) {
                fscanf(file, "%i", &info->armorPrice[i][j][1]);

                if (info->armorPrice[i][j][0] == 2) {
                    fscanf(file, "%i", &info->armorPrice[i][j][2]);
                }
            }

            j += 1;
        }

        i += 1;
    }

    fclose(file);
}

static void loadArmorPosition(struct Resources *info) {
    FILE *armorMeasurements = fopen("dane\\armorMeasurements.txt", "r");
    int i = 0;
    int j = 0;

    while (i < 4) {
        j = 0;
        while (j < 9) {
            fscanf(armorMeasurements, "%i %i", &info->armorPosition[i][j][0], &info->armorPosition[i][j][1]);

            j += 1;
        }

        i += 1;
    }

    fclose(armorMeasurements);
}

static void loadWeapons(struct Resources *info) {
    FilePathList files = LoadDirectoryFiles("resources\\textures\\przedmioty\\weapon");
    int i = 0;

    info->weaponsQuantity = files.capacity;

    info->weapons = malloc(sizeof(Texture2D) * info->weaponsQuantity);
    while (i < info->weaponsQuantity) {
        info->weapons[i] = LoadTexture(TextFormat("resources\\textures\\przedmioty\\weapon\\%i.png", i));

        i += 1;
    }

    UnloadDirectoryFiles(files);
}

static void loadWeaponPrice(struct Resources *info) {
    FILE *file = fopen("dane\\przedmioty\\weapon.txt", "r");
    int j = 0;
    int quantity = 0;

    fscanf(file, "%i", &quantity);
    info->weaponPrice = malloc(sizeof(int[3]) * quantity);

    j = 0;
    while (j < quantity) {
        fscanf(file, "%i", &info->weaponPrice[j][0]);

        if (info->weaponPrice[j][0] != 0) {
            fscanf(file, "%i", &info->weaponPrice[j][1]);

            if (info->weaponPrice[j][0] == 2) {
                fscanf(file, "%i", &info->weaponPrice[j][2]);
            }
        }

        j += 1;
    }

    fclose(file);
}

static void loadItems(struct Resources *info) {
    FilePathList files = LoadDirectoryFiles("resources\\textures\\przedmioty\\inne");
    int i = 0;

    info->itemsQuantity = files.capacity;

    info->items = malloc(sizeof(Texture2D) * info->itemsQuantity);
    while (i < info->itemsQuantity) {
        info->items[i] = LoadTexture(TextFormat("resources\\textures\\przedmioty\\inne\\%i.png", i));

        i += 1;
    }

    UnloadDirectoryFiles(files);
}

static void loadItemPrice(struct Resources *info) {
    FILE *file = fopen("dane\\przedmioty\\inne.txt", "r");
    int j = 0;
    int quantity = 0;

    fscanf(file, "%i", &quantity);
    info->itemsPrice = malloc(sizeof(int[3]) * quantity);

    j = 0;
    while (j < quantity) {
        fscanf(file, "%i", &info->itemsPrice[j][0]);

        if (info->itemsPrice[j][0] != 0) {
            fscanf(file, "%i", &info->itemsPrice[j][1]);

            if (info->itemsPrice[j][0] == 2) {
                fscanf(file, "%i", &info->itemsPrice[j][2]);
            }
        }

        j += 1;
    }

    fclose(file);
}

static void loadFloorTextures(struct Resources *this) {
    FilePathList f = LoadDirectoryFiles("resources\\textures\\floor");
    unsigned int i = 0;

    this->floorTextureQuantity = f.capacity;
    this->floorTextures = malloc(sizeof(Texture2D) * f.capacity);

    while (i < f.capacity) {
        this->floorTextures[i] = LoadTexture(TextFormat("resources\\textures\\floor\\%i.png", i));

        i += 1;
    }

    UnloadDirectoryFiles(f);
}

static void loadWallTextures(struct Resources *this) {
    FilePathList f = LoadDirectoryFiles("resources\\textures\\wall");
    unsigned int i = 0;

    this->wallTextureQuantity = f.capacity;
    this->wallTextures = malloc(sizeof(Texture2D) * f.capacity);

    while (i < f.capacity) {
        this->wallTextures[i] = LoadTexture(TextFormat("resources\\textures\\wall\\%i.png", i));

        i += 1;
    }

    UnloadDirectoryFiles(f);
}

void loadResources(struct Resources *this) {
    SetFonts(this);
    loadMusic(this);
    loadBodyPosition(this);
    loadBodyParts(this);
    loadArmor(this);
    loadArmorPrice(this);
    loadArmorPosition(this);
    loadWeapons(this);
    loadWeaponPrice(this);
    loadItems(this);
    loadItemPrice(this);
    loadFloorTextures(this);
    loadWallTextures(this);
}