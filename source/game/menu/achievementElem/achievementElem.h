#ifndef ACHIEVEMENTELEM_H
#define ACHIEVEMENTELEM_H

#include <raylib.h>
#include <stdlib.h>

#include "button.h"
#include "savefile.h"

struct achievementElem {
    int x;
    int y;
    int space;
    Font* font;
    struct button name;
    struct button description;
    struct button status;
    int numberOfRequirements;
    struct button *requirements;
};

inline void DrawAchievementElem(struct achievementElem element) {
    DrawButton(element.name);
    DrawButton(element.description);
    for (int i = 0; i < element.numberOfRequirements; i++) {
        DrawButton(element.requirements[i]);
    }
    DrawButton(element.status);
}

void UpdateAchievementElem(struct achievementElem* element, struct Achievement achievement);
#endif
