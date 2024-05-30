#ifndef RESOURCES_H
#define RESOURCES_H

#include <raylib.h>

struct Resources {
    Font *fonts;
    int fontsQuantity;

    Music *music;
    int musicQuantity;

    Texture2D(*bodyParts[10])[4];
    int height;
    int width;
    int bodyPosition[4][10][2];
    int bodyPartsQuantity[10];

    Texture2D(*armorPart[9])[4];
    int(*armorPrice[9])[3];
    int armorPosition[4][9][2];
    int armorPartsQuantity[10];

    Texture2D *weapons;
    int(*weaponPrice)[3];
    int weaponsQuantity;

    Texture2D *items;
    int(*itemsPrice)[3];
    int itemsQuantity;

    Texture2D *floors;
    int floorQuantity;

    Texture2D *walls;
    int wallQuantity;
};

void LoadResources(struct Resources *this);
void UnloadResources(struct Resources *this);

enum BodyPartTexture {
    HEAD,
    TORSO,
    LEFT_ARM,
    RIGHT_ARM,
    LEFT_LEG,
    RIGHT_LEG,
    LEFT_HAND,
    RIGHT_HAND,
    LEFT_FOOT,
    RIGHT_FOOT
};

enum ArmorPartTexture {
    HELMET,
    BREASTPLATE,
    PANTS,
    LEFT_BOOT,
    RIGHT_BOOT,
    LEFT_GLOVE,
    RIGHT_GLOVE,
    LEFT_SLEEVE,
    RIGHT_SLEEVE
};

#endif