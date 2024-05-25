#include "playState.h"
#include "load.h"
#include "character.h"

#include "characterCreatorThing.h"

/**
void InitializeCharacterCreator(struct characterCreator* element, struct menuInfo* info) {
    loadBodyParts(&(element->playInfo));
    loadBodyPosition(&(element->playInfo));
    element->character.direction = FRONT;
    for (int i = 0; i < 10; i++) {
        element->character.bodyPart[i] = 0;
        element->playInfo.bodyPosition[0][i][0] /= 2;
        element->playInfo.bodyPosition[0][i][0] += 50;
        element->playInfo.bodyPosition[0][i][1] /= 2;
        element->playInfo.bodyPosition[0][i][1] += 100;

        element->bodyPartSlideBoxes[i] = (struct slideBox){
            .isActive = false,
            .currentOption = 0,
            .optionsET = NULL,
            .init = {
                .x = (GetScreenWidth() >> 1),
                .y = 150 + i * 32,
                .incX = 5,
                .incY = 3,
                .posX = 1,
                .posY = 1,
                .width = 200,
                .optionTime = 1,
            },
            .font = &info->fonts[1],
            .fontSize = 20,
            .fontColor = BLACK,
            .color = GREEN,
            .borderActiveColor = RED,
            .borderColor = BLACK,
            .spaceing = 0
        };
        CalculateSlideBoxPosition(&element->bodyPartSlideBoxes[i]);
    }
    char *bodyPartsInPolish[10] = {
        [HEAD] = "G³owa",
        [LEFT_ARM] = "Lewe ramiê",
        [RIGHT_ARM] = "Prawie ramiê",
        [LEFT_FOOT] = "Lewa stopa",
        [RIGHT_FOOT] = "Prawa stopa",
        [LEFT_HAND] = "Lewa d³oñ",
        [RIGHT_HAND] = "Prawa d³oñ",
        [LEFT_LEG] = "Lewa noga",
        [RIGHT_LEG] = "Prawa d³oñ",
        [TORSO] = "Tors"
    };
    element->bodyPartSlideBoxes[HEAD].numberOfOptions = 4;
    element->bodyPartSlideBoxes[LEFT_ARM].numberOfOptions = 1;
    element->bodyPartSlideBoxes[RIGHT_ARM].numberOfOptions = 1;
    element->bodyPartSlideBoxes[LEFT_FOOT].numberOfOptions = 1;
    element->bodyPartSlideBoxes[RIGHT_FOOT].numberOfOptions = 1;
    element->bodyPartSlideBoxes[LEFT_HAND].numberOfOptions = 1;
    element->bodyPartSlideBoxes[RIGHT_HAND].numberOfOptions = 1;
    element->bodyPartSlideBoxes[LEFT_LEG].numberOfOptions = 1;
    element->bodyPartSlideBoxes[RIGHT_LEG].numberOfOptions = 1;
    element->bodyPartSlideBoxes[TORSO].numberOfOptions = 1;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < element->bodyPartSlideBoxes[i].numberOfOptions; j++) {
            element->bodyPartSlideBoxes[i].options[j] = bodyPartsInPolish[i];
        }
    }

    loadArmor(&(element->playInfo));
    loadArmorPosition(&(element->playInfo));
    for (int i = 0; i < 9; i++) {
        element->character.armorPart[i] = 0;
        element->playInfo.armorPosition[0][i][0] /= 2;
        element->playInfo.armorPosition[0][i][0] += 50;
        element->playInfo.armorPosition[0][i][1] /= 2;
        element->playInfo.armorPosition[0][i][1] += 100;

        element->armorSlideBoxes[i] = (struct slideBox){
            .isActive = false,
            .currentOption = 0,
            .init = {
                .x = (GetScreenWidth() >> 1) + 250,
                .y = 150 + i * 32,
                .incX = 5,
                .incY = 3,
                .posX = 1,
                .posY = 1,
                .width = 200
            },
            .font = &info->fonts[1],
            .fontSize = 20,
            .fontColor = BLACK,
            .color = GREEN,
            .borderActiveColor = RED,
            .borderColor = BLACK,
            .spaceing = 0
        };
        CalculateSlideBoxPosition(&element->armorSlideBoxes[i]);
    }
    char *armorPartsInPolish[] = {
        [HELMET] = "He³m",
        [BREASTPLATE] = "Napierœnik",
        [PANTS] = "Spodnie",
        [LEFT_BOOT] = "Lewy but",
        [RIGHT_BOOT] = "Prawy but",
        [LEFT_GLOVE] = "Lewa rêkawica",
        [RIGHT_GLOVE] = "Prawa rêkawica",
        [LEFT_SLEEVE] = "Lewy rêkaw",
        [RIGHT_SLEEVE] = "Prawy rêkaw"
    };
    element->armorSlideBoxes[HELMET].numberOfOptions = 1;
    element->armorSlideBoxes[BREASTPLATE].numberOfOptions = 1;
    element->armorSlideBoxes[PANTS].numberOfOptions = 1;
    element->armorSlideBoxes[LEFT_BOOT].numberOfOptions = 1;
    element->armorSlideBoxes[RIGHT_BOOT].numberOfOptions = 1;
    element->armorSlideBoxes[LEFT_GLOVE].numberOfOptions = 1;
    element->armorSlideBoxes[RIGHT_GLOVE].numberOfOptions = 1;
    element->armorSlideBoxes[LEFT_SLEEVE].numberOfOptions = 1;
    element->armorSlideBoxes[RIGHT_SLEEVE].numberOfOptions = 1;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < element->armorSlideBoxes[i].numberOfOptions; j++) {
            element->armorSlideBoxes[i].options[j] = armorPartsInPolish[i];
        }
    }
}

void DrawCharacterCreator( struct characterCreator *element, struct menuInfo* info) {
    struct button title = {
        .text = "Kreator postaci",
        .isActive = 1,
        .init = {
            .x = GetScreenWidth() >> 1,
            .y = 10,
            .incX = 10,
            .incY = 10,
            .posX = 1,
            .posY = 0,
        },
        .font = &info->fonts[0],
        .fontSize = 100,
        .fontColor = BLACK,
        .color = BLANK,
        .hoverColor = BLANK,
        .spaceing = 0,
    };

    struct button goBack = {
        .text = "Zapisz",
        .isActive = 1,
        .init = {
            .x = GetScreenWidth() >> 1,
            .y = (GetScreenHeight() >> 1) + 200,
            .incX = 10,
            .incY = 10,
            .posX = 1,
            .posY = 1
        },
        .font = &info->fonts[0],
        .fontSize = 20,
        .fontColor = BLACK,
        .color = GREEN,
        .hoverColor = DARKGRAY,
        .spaceing = 0
    };    
    CalculateButtonPosition(&title);
    CalculateButtonPosition(&goBack);
    DrawButton(title);
    DrawButton(goBack);

    for (int i = 0; i < 10; i++) {
        DrawSlideBox(&element->bodyPartSlideBoxes[i]);
        UpdateSlideBox(&element->bodyPartSlideBoxes[i]);
    }
    Vector2 texturePosition;
    for (int i = 0; i < 10; i++) {
        texturePosition = (Vector2){
            .x = (float)element->playInfo.bodyPosition[0][i][0],
            .y = (float)element->playInfo.bodyPosition[0][i][1],
        };
        int bodyPartIndex = element->bodyPartSlideBoxes[i].currentOption;
        DrawTextureEx(*element->playInfo.bodyParts[i][bodyPartIndex], texturePosition, 0, 0.5, WHITE);
    }

    for (int i = 0; i < 9; i++) {
        DrawSlideBox(&element->armorSlideBoxes[i]);
        UpdateSlideBox(&element->armorSlideBoxes[i]);
    }
    for (int i = 0; i < 9; i++) {
        texturePosition = (Vector2){
            .x = (float)element->playInfo.armorPosition[0][i][0],
            .y = (float)element->playInfo.armorPosition[0][i][1],
        };
        int armorPartIndex = element->armorSlideBoxes[i].currentOption;
        DrawTextureEx(*element->playInfo.armorPart[i][armorPartIndex], texturePosition, 0, 0.5, WHITE);
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (isMouseOver(goBack)) {
            element->isActive = 0;
        }
    }
}
/**/