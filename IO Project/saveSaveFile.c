#include <stdio.h>
#include <time.h>

#include "savefile.h"

static void CreateDate(const char *const saveName) {
    FILE *file = fopen(saveName, "w");
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    fprintf(file, "%i ", tm.tm_year + 1900);
    fprintf(file, "%i ", tm.tm_mon + 1);
    fprintf(file, "%i ", tm.tm_mday);
    fprintf(file, "%i ", tm.tm_hour);
    fprintf(file, "%i ", tm.tm_min);
    fprintf(file, "%i", tm.tm_sec);

    fclose(file);
}

static void SaveBody(FILE *playerFile, struct character *character) {
    int i = 0;

    while (i < 10) {
        fprintf(playerFile, "%i\n", character->bodyPart[i]);

        i += 1;
    }
    fprintf(playerFile, "\n");
}

static void SaveArmor(FILE *playerFile, struct character *character) {
    int i = 0;

    while (i < 9) {
        fprintf(playerFile, "%i\n", character->armorPart[i]);

        i += 1;
    }
    fprintf(playerFile, "\n");
}

static void SaveCharacter(struct character *character, const char *characterSave) {
    FILE *playerFile = fopen(characterSave, "w");
    struct Object2D *object = &character->object;

    fprintf(playerFile, "%s\n", character->name);
    fprintf(playerFile, "%f %f\n\n", object->sizeV.x, object->sizeV.y);

    SaveBody(playerFile, character);
    SaveArmor(playerFile, character);

    fprintf(playerFile, "%i", character->weapon);

    fclose(playerFile);
}

static void SaveEquipment(struct player *player, const char *fileName) {
    FILE *file = fopen(fileName, "w");
    int i = 0;

    while (i < 25) {
        fprintf(file, "% 4s%i ", "", player->equipment[i][0]);

        if (player->equipment[i][0] != 0) {
            fprintf(file, "%i ", player->equipment[i][1]);

            if (player->equipment[i][0] == 2) {
                fprintf(file, "%i ", player->equipment[i][2]);
            }
        }

        fprintf(file, "\n");

        i += 1;
    }

    fclose(file);
}

static void SavePosition(struct SaveFile *this) {
    FILE *file = fopen(TextFormat("saves\\%s\\mapy\\position.txt", this->saveName), "w");

    fprintf(file, "%i %f %f", this->mapID, this->player.character.object.position.x, this->player.character.object.position.z);

    fclose(file);
}

static void SavePlayer(struct SaveFile *this) {
    SaveCharacter(&this->player.character, TextFormat("saves\\%s\\postaæ.txt", this->saveName));
    SaveEquipment(&this->player, TextFormat("saves\\%s\\ekwipunek.txt", this->saveName));
    SavePosition(this);
}

static void SaveShop(int shopEQ[10][3], const char *fileName) {
    FILE *file = fopen(fileName, "w");
    int i = 0;

    while (i < 10) {
        fprintf(file, "% 4s%i ", "", shopEQ[i][0]);

        if (shopEQ[i][0] != 0) {
            fprintf(file, "%i ", shopEQ[i][1]);

            if (shopEQ[i][0] == 2) {
                fprintf(file, "%i ", shopEQ[i][2]);
            }
        }

        fprintf(file, "\n");

        i += 1;
    }

    fclose(file);
}

static void SaveShops(struct SaveFile *this) {
    int i = 0;

    while (i < this->shopQuantity) {
        SaveShop(this->shopEquipment[i], TextFormat("saves\\%s\\sklepy\\%i.txt", this->saveName, i));

        i += 1;
    }
}

static void SaveFloors(FILE *file, struct SaveFile *this) {
    int i = 0;

    fprintf(file, "%i\n", this->floorsQuantity);
    while (i < this->floorsQuantity) {
        fprintf(file, "% 4s%i %f %f %f\n% 8s%f %f\n% 8s%f %f\n", "",
            this->floors[i].ID,
            this->floors[i].object.sizeV.x,
            this->floors[i].object.sizeV.y,
            this->floors[i].object.position.y,
            "",
            this->floors[i].object.position.x,
            this->floors[i].object.position.z,
            "",
            this->floors[i].actualSize.x,
            this->floors[i].actualSize.y
        );

        i += 1;
    }
}

static void SaveCeilings(FILE *file, struct SaveFile *this) {
    int i = 0;

    fprintf(file, "%i\n", this->ceilingQuantity);
    while (i < this->ceilingQuantity) {
        fprintf(file, "% 4s%i %f %f %f\n% 8s%f %f\n% 8s%f %f\n", "",
            this->ceiling[i].ID,
            this->ceiling[i].object.sizeV.x,
            this->ceiling[i].object.sizeV.y,
            this->ceiling[i].object.position.y,
            "",
            this->ceiling[i].object.position.x,
            this->ceiling[i].object.position.z,
            "",
            this->ceiling[i].actualSize.x,
            this->ceiling[i].actualSize.y
        );

        i += 1;
    }
}

static void SaveWalls(FILE *file, struct SaveFile *this) {
    int i = 0;

    fprintf(file, "%i\n", this->wallQuantity);
    while (i < this->wallQuantity) {
        fprintf(file, "% 4s%i %f %f %f %f %f %f %f %f\n", "",
            this->walls[i].ID,
            this->walls[i].object.sizeV.x,
            this->walls[i].object.sizeV.y,
            this->walls[i].object.position.x,
            this->walls[i].object.position.y,
            this->walls[i].object.position.z,
            this->walls[i].endPosition.x,
            this->walls[i].endPosition.y,
            this->walls[i].endPosition.z
        );

        i += 1;
    }
}

static void SaveEnemies(FILE *file, struct SaveFile *this) {
    int i = 0;

    fprintf(file, "%i\n", this->enemyQuantity);
    while (i < this->enemyQuantity) {
        fprintf(file, "% 4s%i %i %f %f\n", "", this->enemies[i].ID, this->enemies[i].dialog, this->enemies[i].object.position.x, this->enemies[i].object.position.z);

        i += 1;
    }
}

static void SaveSellers(FILE *file, struct SaveFile *this) {
    int i = 0;

    fprintf(file, "%i", this->sellersQuantity);
    while (i < this->sellersQuantity) {
        fprintf(file, "% 4s%i %i %i %f %f\n", "", this->sellers[i].character.ID, this->sellers[i].shopID, this->sellers[i].character.dialog, this->sellers[i].character.object.position.x, this->sellers[i].character.object.position.z);

        i += 1;
    }
}

static void SaveMap(struct SaveFile *this) {
    FILE *mapFile = fopen(TextFormat("saves\\%s\\mapy\\0.txt", this->saveName), "w");

    SaveFloors(mapFile, this);
    SaveCeilings(mapFile, this);
    SaveWalls(mapFile, this);
    SaveEnemies(mapFile, this);
    SaveSellers(mapFile, this);

    fclose(mapFile);
}

void SaveSaveFile(struct SaveFile *this) {
    CreateDate(TextFormat("saves\\%s\\date.txt", this->saveName));

    SavePlayer(this);
    SaveShops(this);
    SaveMap(this);
}