#include <raylib.h>

#include "character.h"

struct fighterLabelPositionParameters {
    int x;
    int y;
    int incX;
    int incY;
    int posX; // 0 - left, 1 - center, 2 - right
    int posY; // 0 - up, 1 - center, 2 - bottom
    int height;
    int *((*durability)[9]);
    Vector3 position;
};

struct fighterLabel {
    int barWidth;
    int barGap;

    int maxHealth;
    int maxRest; // wypoczêcie

    int health;
    int rest;
    int durability;

    struct character fighter;
	union {
        struct fighterLabelPositionParameters init;
        struct {
            Vector2 leftCorner;
            Vector2 name;
            RenderTexture render;
            int maxDurability; // armor thing
            int height;
            int width;
        };
	};

    Font *font;
    int fontSize;
    Color fontColor;
    int spaceing;

    Color color;
};

struct Resources;
void InitializeFighterLabel(struct fighterLabel *this, struct Resources *resources);
void FreeFighterLabel(struct fighterLabel *this);

void DrawFighterLabel(struct fighterLabel *this);
void UpdateFighterLabel(struct fighterLabel *this);