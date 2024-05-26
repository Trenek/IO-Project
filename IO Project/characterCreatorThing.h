#ifndef CHARACTERCREATOR_H
#define CHARACTERCREATOR_H

#include "button.h"
#include "playState.h"
#include "slideBox.h"
#include <raylib.h>

/**
struct characterCreator {
 //   bool isActive;
 //   struct playInfo playInfo;
    struct character character;
 //   struct slideBox bodyPartSlideBoxes[10];
 //   struct slideBox 
 
 SlideBoxes[9];
};

void InitializeCharacterCreator(struct characterCreator* element, struct menuInfo* info);

void DrawCharacterCreator(struct characterCreator *element, struct menuInfo* info);

inline void getChoosenBodyParts(struct characterCreator element, int *bodyParts) {
    for (int i = 0; i < 10; i++) {
        bodyParts[i] = element.bodyPartSlideBoxes[i].currentOption;
    }
}

inline void getChoosenArmorParts(struct characterCreator element, int* armorParts) {
    for (int i = 0; i < 9; i++) {
        armorParts[i] = element.armorSlideBoxes[i].currentOption;
    }
}
/**/
#endif
