#include "achievementElem.h"

void UpdateAchievementElem(struct achievementElem *element, struct Achievement achievement) {
    element->numberOfRequirements = achievement.requirementsCount;
    element->name = (struct button){
        .text = achievement.name,
        .isActive = 1,
        .init = {
            .x = element->x,
            .y = element->y,
            .incX = 10,
            .incY = 10,
            .posX = 1,
            .posY = 1
        },
        .font = element->font,
        .fontSize = 32,
        .fontColor = BLACK,
        .color = BLANK,
        .hoverColor = BLANK,
        .spaceing = 0
    };
    element->description = (struct button){
        .text = achievement.description,
        .isActive = 1,
        .init = {
            .x = element->x,
            .y = element->y + element->space,
            .incX = 10,
            .incY = 10,
            .posX = 1,
            .posY = 1
        },
        .font = element->font,
        .fontSize = 25,
        .fontColor = BLACK,
        .color = BLANK,
        .hoverColor = BLANK,
        .spaceing = 0
    };
    element->status = (struct button){
        .text = achievement.status == 1 ? "Zakończone" : "Niezakończone",
        .isActive = 1,
        .init = {
            .x = element->x,
            .y = element->y + 2 * element->space,
            .incX = 10,
            .incY = 10,
            .posX = 1,
            .posY = 1
        },
        .font = element->font,
        .fontSize = 22,
        .fontColor = achievement.status == 1 ? GREEN : RED,
        .color = BLANK,
        .hoverColor = BLANK,
        .spaceing = 0
    };

    element->requirements = (struct button*)malloc(element->numberOfRequirements * sizeof(struct button));
    for (int i = 0; i < element->numberOfRequirements; i++) {
        element->requirements[i] = (struct button){
            .text = achievement.requirements[i],
            .isActive = 1,
            .init = {
                .x = element->x,
                .y = element->y + (3 + i) * element->space,
                .incX = 10,
                .incY = 10,
                .posX = 1,
                .posY = 1
            },
            .font = element->font,
            .fontSize = 20,
            .fontColor = BLACK,
            .color = BLANK,
            .hoverColor = BLANK,
            .spaceing = 0
        };

        CalculateButtonPosition(&element->requirements[i]);
    }

    CalculateButtonPosition(&element->name);
    CalculateButtonPosition(&element->description);
    CalculateButtonPosition(&element->status);
}