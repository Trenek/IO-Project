#define _USE_MATH_DEFINES

#include <math.h>
#include <stdio.h>

#include <raylib.h>
#include <raymath.h>

#include "playState.h"
#include "player.h"

#define GRAVITY -9.81f
#define M_PIF ((float)M_PI)

void movePlayer(struct playInfo *info, struct player* player, Camera* cam) {
    Vector3 * const position = &player->character.object.position;

    Vector2 ve = {
        .x = position->x - cam->position.x,
        .y = position->z - cam->position.z,
    };
    Vector2 veH = { 0 };
    float deltaTime = GetFrameTime();

    ve = Vector2Normalize(ve);

    ve.x *= 5 * deltaTime;
    ve.y *= 5 * deltaTime;

    if (IsKeyDown(KEY_LEFT_SHIFT)) {
        ve.x *= 1.5;
        ve.y *= 1.5;
    }

    if (IsKeyDown(KEY_W)) {
        position->x += ve.x;
        position->z += ve.y;
        cam->position.x += ve.x;
        cam->position.z += ve.y;
        if (player->character.direction != BACK) {
            player->character.direction = BACK;

            assemblePlayerTexture(info->resources, &player->character);
        }
    }
    else if (IsKeyDown(KEY_S)) {
        veH = Vector2Rotate(ve, M_PIF);
        position->x += veH.x;
        position->z += veH.y;
        cam->position.x += veH.x;
        cam->position.z += veH.y;
        if (player->character.direction != FRONT) {
            player->character.direction = FRONT;

            assemblePlayerTexture(info->resources, &player->character);
        }
    }
    else if (IsKeyDown(KEY_D)) {
        veH = Vector2Rotate(ve, M_PIF / 2);
        position->x += veH.x;
        position->z += veH.y;
        cam->position.x += veH.x;
        cam->position.z += veH.y;
        if (player->character.direction != RIGHT) {
            player->character.direction = RIGHT;

            assemblePlayerTexture(info->resources, &player->character);
        }
    }
    else if (IsKeyDown(KEY_A)) {
        veH = Vector2Rotate(ve, (3 * M_PIF) / 2);
        position->x += veH.x;
        position->z += veH.y;
        cam->position.x += veH.x;
        cam->position.z += veH.y;
        if (player->character.direction != LEFT) {
            player->character.direction = LEFT;

            assemblePlayerTexture(info->resources, &player->character);
        }
    }
    else {
        if (player->character.direction != FRONT) {
           // player->character.direction = FRONT;

            //assemblePlayerTexture(info->resources, &player->character);
        }
    }

    if (IsCursorHidden()) {
        player->a += GetMouseDelta().y * GetFrameTime() / 4;
        player->b += GetMouseDelta().x * GetFrameTime() / 4;
        player->r -= GetMouseWheelMove() / 4;

        if (player->a < 1 * PI / 180) {
            player->a = 1 * PI / 180;
        }
        else if (player->a > 70 * PI / 180) {
            player->a = 70 * PI / 180;
        }

        if (player->r < player->character.object.sizeV.x) {
            player->r = player->character.object.sizeV.x;
        }
    }

    if (position->y == 0.0f)
        if (IsKeyPressed(KEY_SPACE)) player->speedY = 5;

    if (position->y >= 0.0f) {
        if (!(position->y == 0.0f && player->speedY == 0)) {
            position->y += ((player->speedY) + ((GRAVITY) * deltaTime / 2.0f)) * deltaTime;
            if (position->y < 0.0f) {
                position->y = 0.0f;
            }
            player->speedY = player->speedY + (GRAVITY * deltaTime);
        }
    }
    else {
        position->y = 0.0f;
        player->speedY = 0;
    }
}

void gravity(struct player* player) {
    Vector3 * const position = &player->character.object.position;

    float deltaTime = GetFrameTime();

    if (position->y >= 0.0f) {
        if (!(position->y == 0.0f && player->speedY == 0)) {
            position->y += ((player->speedY) + ((GRAVITY) * deltaTime / 2.0f)) * deltaTime;
            if (position->y < 0.0f) {
                position->y = 0.0f;
            }
            player->speedY = player->speedY + (GRAVITY * deltaTime);
        }
    }
    else {
        position->y = 0.0f;
        player->speedY = 0;
    }
}