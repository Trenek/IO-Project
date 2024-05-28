#ifndef ARMOR_H
#define ARMOR_H
struct playInfo;

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

void loadArmor(struct playInfo *info);
void unloadArmor(struct playInfo *info);
#endif