#ifndef BODYPARTS_H
#define BODYPARTS_H

struct menuInfo;
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

void loadBodyParts(struct menuInfo *info);
void unloadBodyParts(struct menuInfo *info);
void loadBodyPosition(struct menuInfo *info);

#endif