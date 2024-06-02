#include "fighterLabel.h"
#include "character.h"
#include "resources.h"

void InitializeFighterLabel(struct fighterLabel *this, struct Resources *resources) {
    struct fighterLabelPositionParameters init = this->init;
    const int width = 3 * init.height;

    this->leftCorner = (Vector2){
        .x = init.x - (init.posX * width) / 2.0f,
        .y = init.y - (init.posY * init.height) / 2.0f
    };

    this->name = (Vector2){
        .x = this->leftCorner.x + init.height,
        .y = this->leftCorner.y
    };

    this->width = width;
    this->height = init.height;

    this->fighter.direction = FRONT;
    assemblePlayerTexture(resources, &this->fighter);

    this->render = LoadRenderTexture((int)this->width, (int)this->height);
    this->health = this->maxHealth;
    this->durability = this->maxDurability;
    this->rest = this->maxRest;
}

void FreeFighterLabel(struct fighterLabel *this) {
    UnloadRenderTexture(this->render);
}


void DrawFighterLabel(struct fighterLabel *this) {
    DrawTextureEx(this->render.texture, this->leftCorner, 0.0f, 1.0f, WHITE);
}

void UpdateFighterLabel(struct fighterLabel *this) {
    RenderTexture temp = LoadRenderTexture((int)this->width, (int)this->height);

    BeginTextureMode(temp);
        ClearBackground(this->color);
        DrawTextureEx(*this->fighter.object.texture, (Vector2) { 0.0f, 0.0f }, 0.0f, (float)this->height / this->fighter.object.texture->width, WHITE);
        DrawTextEx(*this->font, this->fighter.name, (Vector2) { (float)this->height, 0 }, (float)this->fontSize, (float)this->spaceing, this->fontColor);
        DrawRectangle(this->height, this->fontSize, this->height * 15 / 8, this->barWidth, DARKBROWN);
        DrawRectangle(this->height, this->fontSize, (this->height * 15 / 8) * this->health / this->maxHealth, this->barWidth, RED);
        DrawRectangle(this->height, this->fontSize + this->barWidth + this->barGap, this->height * 15 / 8, this->barWidth, DARKBROWN);
        DrawRectangle(this->height, this->fontSize + this->barWidth + this->barGap, (this->height * 15 / 8) * this->durability / this->maxDurability, this->barWidth, BLUE);
        DrawRectangle(this->height, this->fontSize + (this->barWidth + this->barGap) * 2, this->height * 15 / 8, this->barWidth, DARKBROWN);
        DrawRectangle(this->height, this->fontSize + (this->barWidth + this->barGap) * 2, (this->height * 15 / 8) * this->rest / this->maxRest, this->barWidth, GREEN);
    EndTextureMode();

    BeginTextureMode(this->render);
        ClearBackground(WHITE);
        DrawTextureEx(temp.texture, (Vector2) { 0.0f, 0.0f }, 0.0f, 1.0f, WHITE);
    EndTextureMode();

    UnloadRenderTexture(temp);
}