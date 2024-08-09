#include <stdio.h>
#include <stdlib.h>
#include <uchar.h>

#include "resources.h"
#include "fscanfWithAllocation.h"

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

static void LoadFonts(struct Resources *this) {
    char32_t letters[] = U"?!,._<>:()^-/*aąbcćdeęfghijklłmnńoópqrsśtuvwxyzźżAĄBCĆDEĘFGHIJKLŁMNŃOÓPQRSŚTUVWXYZŹŻ1234567890";
    Font fonts[] = {
        LoadFontEx("resources/fonts/font2.ttf", 100, letters, sizeof(letters) / sizeof(int)),
        LoadFontEx("resources/fonts/font5.ttf", 100, letters, sizeof(letters) / sizeof(int))
    };
    int i = 0;

    this->fontsQuantity = sizeof(fonts) / sizeof(Font);
    this->fonts = malloc(sizeof(fonts));

    while (i < this->fontsQuantity) {
        this->fonts[i] = fonts[i];
        GenTextureMipmaps(&this->fonts[i].texture);
        SetTextureFilter(this->fonts[i].texture, TEXTURE_FILTER_POINT);

        i += 1;
    }
}

static void LoadMusic(struct Resources *this) {
    InitAudioDevice();

    Music music[] = {
        LoadMusicStream("resources/music/music1.mp3"),
        LoadMusicStream("resources/music/music2.mp3")
    };
    int i = 0;

    this->music = malloc(sizeof(music));
    this->musicQuantity = sizeof(music) / sizeof(Music);
    while (i < this->musicQuantity) {
        this->music[i] = music[i];
        i += 1;
    }

    i = 0;
    while (i < this->musicQuantity) {
        PlayMusicStream(this->music[i]);
        i += 1;
    }
}

static void LoadBodyPosition(struct Resources *this) {
    FILE *bodyMeasurements = fopen("dane\\measurements\\body.txt", "r");
    int i = 0;
    int j = 0;

    fscanf(bodyMeasurements, "%i %i", &this->width, &this->height);

    while (i < 4) {
        j = 0;
        while (j < 10) {
            fscanf(bodyMeasurements, "%i %i", &this->bodyPosition[j][i][0], &this->bodyPosition[j][i][1]);

            j += 1;
        }

        i += 1;
    }

    fclose(bodyMeasurements);
}

static void loadBodyPart(int num, struct Resources *this) {
    const char *const directory = TextFormat("resources\\textures\\body\\%s", bodyPartsNames[num]);
    char buffor[128];
    FilePathList files = LoadDirectoryFiles(directory);
    unsigned int i = 0;
    unsigned int j = 0;

    this->bodyPartsQuantity[num] = files.capacity;
    this->bodyParts[num] = malloc(sizeof(Texture2D[4]) * files.capacity);

    while (i < files.capacity) {
        j = 0;
        while (j < 4) {
            sprintf(buffor, "%s\\%i\\%i\\0.png", directory, i, j);
            this->bodyParts[num][i][j] = LoadTexture(buffor);
            j += 1;
        }

        i += 1;
    }

    UnloadDirectoryFiles(files);
}

static void LoadBodyParts(struct Resources *this) {
    int i = 0;

    while (i < 10) {
        loadBodyPart(i, this);

        i += 1;
    }
}

static void loadArmorPart(int num, struct Resources *this) {
    const char *const directory = TextFormat("resources\\textures\\przedmioty\\armor\\%s", armorNames[num]);
    char buffor[128];
    FilePathList files = LoadDirectoryFiles(directory);
    unsigned int i = 0;
    unsigned int j = 0;

    this->armorPart[num] = malloc(sizeof(Texture2D[4]) * files.capacity);
    this->armorPartsQuantity[num] = files.capacity;

    while (i < files.capacity) {
        j = 0;
        while (j < 4) {
            sprintf(buffor, "%s\\%i\\%i\\0.png", directory, i, j);
            this->armorPart[num][i][j] = LoadTexture(buffor);
            j += 1;
        }

        i += 1;
    }

    UnloadDirectoryFiles(files);
}

static void LoadArmor(struct Resources *this) {
    int i = 0;

    while (i < 9) {
        loadArmorPart(i, this);

        i += 1;
    }
}

static void LoadArmorInfo(struct Resources *this) {
    FILE *file = fopen("dane\\przedmioty\\armor.txt", "r");
    int i = 0;
    int j = 0;
    int quantity = 0;

    while (i < 9) {
        fscanf(file, "%i", &quantity);
        this->armorPrice[i] = malloc(sizeof(int[3]) * quantity);
        this->armorDurability[i] = malloc(sizeof(int) * quantity);

        j = 0;
        while (j < quantity) {
            fscanf(file, "%i", &this->armorPrice[i][j][0]);

            if (this->armorPrice[i][j][0] != 0) {
                fscanf(file, "%i", &this->armorPrice[i][j][1]);

                if (this->armorPrice[i][j][0] == 2) {
                    fscanf(file, "%i", &this->armorPrice[i][j][2]);
                }
            }

            fscanf(file, "%i", &this->armorDurability[i][j]);

            j += 1;
        }

        i += 1;
    }

    fclose(file);
}

static void LoadArmorPosition(struct Resources *this) {
    FILE *armorMeasurements = fopen("dane\\measurements\\armor.txt", "r");
    int i = 0;
    int j = 0;

    while (i < 4) {
        j = 0;
        while (j < 9) {
            fscanf(armorMeasurements, "%i %i", &this->armorPosition[j][i][0], &this->armorPosition[j][i][1]);

            j += 1;
        }

        i += 1;
    }

    fclose(armorMeasurements);
}

static void LoadWeapons(struct Resources *this) {
    FilePathList files = LoadDirectoryFiles("resources\\textures\\przedmioty\\weapon");
    int i = 0;

    this->weaponsQuantity = files.capacity;

    this->weapons = malloc(sizeof(Texture2D) * this->weaponsQuantity);
    while (i < this->weaponsQuantity) {
        this->weapons[i] = LoadTexture(TextFormat("resources\\textures\\przedmioty\\weapon\\%i.png", i));

        i += 1;
    }

    UnloadDirectoryFiles(files);
}

static void LoadWeaponInfo(struct Resources *this) {
    FILE *file = fopen("dane\\przedmioty\\weapon.txt", "r");
    int j = 0;
    int quantity = 0;

    fscanf(file, "%i", &quantity);
    this->weaponPrice = malloc(sizeof(int[3]) * quantity);
    this->weaponAttack = malloc(sizeof(int) * quantity);

    j = 0;
    while (j < quantity) {
        fscanf(file, "%i", &this->weaponPrice[j][0]);

        if (this->weaponPrice[j][0] != 0) {
            fscanf(file, "%i", &this->weaponPrice[j][1]);

            if (this->weaponPrice[j][0] == 2) {
                fscanf(file, "%i", &this->weaponPrice[j][2]);
            }
        }

        fscanf(file, "%i", &this->weaponAttack[j]);

        j += 1;
    }

    fclose(file);
}

static void LoadWeaponPosition(struct Resources *this) {
    FILE *armorMeasurements = fopen("dane\\measurements\\weapon.txt", "r");

    fscanf(armorMeasurements, "%i %i", &this->weaponPosition[0], &this->weaponPosition[1]);

    fclose(armorMeasurements);
}

static void LoadItems(struct Resources *this) {
    FilePathList files = LoadDirectoryFiles("resources\\textures\\przedmioty\\inne");
    int i = 0;

    this->itemsQuantity = files.capacity;

    this->items = malloc(sizeof(Texture2D) * this->itemsQuantity);
    while (i < this->itemsQuantity) {
        this->items[i] = LoadTexture(TextFormat("resources\\textures\\przedmioty\\inne\\%i.png", i));

        i += 1;
    }

    UnloadDirectoryFiles(files);
}

static void LoadItemPrice(struct Resources *this) {
    FILE *file = fopen("dane\\przedmioty\\inne.txt", "r");
    int j = 0;
    int quantity = 0;

    fscanf(file, "%i", &quantity);
    this->itemsPrice = malloc(sizeof(int[3]) * quantity);

    j = 0;
    while (j < quantity) {
        fscanf(file, "%i", &this->itemsPrice[j][0]);

        if (this->itemsPrice[j][0] != 0) {
            fscanf(file, "%i", &this->itemsPrice[j][1]);

            if (this->itemsPrice[j][0] == 2) {
                fscanf(file, "%i", &this->itemsPrice[j][2]);
            }
        }

        j += 1;
    }

    fclose(file);
}

static void LoadFloors(struct Resources *this) {
    FilePathList f = LoadDirectoryFiles("resources\\textures\\objects\\floor");
    unsigned int i = 0;

    this->floorQuantity = f.capacity;
    this->floors = malloc(sizeof(Texture2D) * f.capacity);

    while (i < f.capacity) {
        this->floors[i] = LoadTexture(TextFormat("resources\\textures\\objects\\floor\\%i.png", i));

        i += 1;
    }

    UnloadDirectoryFiles(f);
}

static void LoadCeiling(struct Resources *this) {
    FilePathList f = LoadDirectoryFiles("resources\\textures\\objects\\ceiling");
    unsigned int i = 0;

    this->ceilingQuantity = f.capacity;
    this->ceiling = malloc(sizeof(Texture2D) * f.capacity);

    while (i < f.capacity) {
        this->ceiling[i] = LoadTexture(TextFormat("resources\\textures\\objects\\ceiling\\%i.png", i));

        i += 1;
    }

    UnloadDirectoryFiles(f);
}

static void LoadWalls(struct Resources *this) {
    FilePathList f = LoadDirectoryFiles("resources\\textures\\objects\\wall");
    unsigned int i = 0;

    this->wallQuantity = f.capacity;
    this->walls = malloc(sizeof(Texture2D) * f.capacity);

    while (i < f.capacity) {
        this->walls[i] = LoadTexture(TextFormat("resources\\textures\\objects\\wall\\%i.png", i));

        i += 1;
    }

    UnloadDirectoryFiles(f);
}

static void LoadAttacks(struct Resources *this) {
    FilePathList f = LoadDirectoryFiles("dane\\walka\\attacks");
    FILE *file = NULL;
    unsigned int i = 0;

    this->attack = malloc(sizeof(struct attack) * f.capacity);
    this->attackQuantity = f.capacity;

    while (i < f.capacity) {
        file = fopen(TextFormat("dane\\walka\\attacks\\%i.txt", (int)i), "r");

        fscanfUnlimited(file, &this->attack[i].name, '\n');
        fscanf(file, "%i %i", &this->attack[i].force, &this->attack[i].cost);

        fclose(file);
        i += 1;
    }
}

void LoadResources(struct Resources *this) {
    LoadFonts(this);
    LoadMusic(this);

    LoadBodyPosition(this);
    LoadBodyParts(this);

    LoadArmorPosition(this);
    LoadArmor(this);
    LoadArmorInfo(this);

    LoadWeapons(this);
    LoadWeaponInfo(this);
    LoadWeaponPosition(this);

    LoadItems(this);
    LoadItemPrice(this);
    LoadFloors(this);
    LoadCeiling(this);
    LoadWalls(this);

    LoadAttacks(this);
}