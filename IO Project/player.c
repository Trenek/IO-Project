#define _USE_MATH_DEFINES

#include <math.h>

#include <raylib.h>
#include <raymath.h>

#include "player.h"

void movePlayer(struct player* player, Camera* cam) {
    Vector2 ve = {
        .x = player->object->position.x - cam->position.x,
        .y = player->object->position.z - cam->position.z,
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

    if (IsKeyDown(KEY_I)) {
        player->object->position.x += ve.x;
        player->object->position.z += ve.y;
        cam->position.x += ve.x;
        cam->position.z += ve.y;
        player->object->state = 1;
    }
    else if (IsKeyDown(KEY_K)) {
        veH = Vector2Rotate(ve, M_PI);
        player->object->position.x += veH.x;
        player->object->position.z += veH.y;
        cam->position.x += veH.x;
        cam->position.z += veH.y;
        player->object->state = 3;
    }
    else if (IsKeyDown(KEY_L)) {
        veH = Vector2Rotate(ve, M_PI / 2);
        player->object->position.x += veH.x;
        player->object->position.z += veH.y;
        cam->position.x += veH.x;
        cam->position.z += veH.y;
        player->object->state = 2;
    }
    else if (IsKeyDown(KEY_J)) {
        veH = Vector2Rotate(ve, (3 * M_PI) / 2);
        player->object->position.x += veH.x;
        player->object->position.z += veH.y;
        cam->position.x += veH.x;
        cam->position.z += veH.y;
        player->object->state = 4;
    }
    else {
        player->object->state = 0;
    }

    if (player->object->position.y == player->object->sizeV.y / 2)
        if (IsKeyPressed(KEY_SPACE)) player->speedY = 5;

    if (player->object->position.y >= player->object->sizeV.y / 2) {
        if (!(player->object->position.y == player->object->sizeV.y / 2 && player->speedY == 0)) {
            player->object->position.y += ((player->speedY) + ((-9.81f) * deltaTime / 2.0f)) * deltaTime;
            if (player->object->position.y < player->object->sizeV.y / 2) {
                player->object->position.y = player->object->sizeV.y / 2;
            }
            player->speedY = player->speedY + (-9.81f * deltaTime);
        }
    }
    else {
        player->object->position.y = player->object->sizeV.y / 2;
        player->speedY = 0;
    }
}

void gravity(struct player* player, Camera* cam) {
    float deltaTime = GetFrameTime();

    if (player->object->position.y >= player->object->sizeV.y / 2) {
        if (!(player->object->position.y == player->object->sizeV.y / 2 && player->speedY == 0)) {
            player->object->position.y += ((player->speedY) + ((-9.81f) * deltaTime / 2.0f)) * deltaTime;
            if (player->object->position.y < player->object->sizeV.y / 2) {
                player->object->position.y = player->object->sizeV.y / 2;
            }
            player->speedY = player->speedY + (-9.81f * deltaTime);
        }
    }
    else {
        player->object->position.y = player->object->sizeV.y / 2;
        player->speedY = 0;
    }
}