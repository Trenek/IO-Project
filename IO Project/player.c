#define _USE_MATH_DEFINES

#include <math.h>

#include <raylib.h>
#include <raymath.h>

#include "player.h"

#define GRAVITY -9.81f
#define M_PIF ((float)M_PI)

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

    if (IsKeyDown(KEY_W)) {
        player->object->position.x += ve.x;
        player->object->position.z += ve.y;
        cam->position.x += ve.x;
        cam->position.z += ve.y;
        //player->object->state = 1;
    }
    else if (IsKeyDown(KEY_S)) {
        veH = Vector2Rotate(ve, M_PIF);
        player->object->position.x += veH.x;
        player->object->position.z += veH.y;
        cam->position.x += veH.x;
        cam->position.z += veH.y;
        //player->object->state = 3;
    }
    else if (IsKeyDown(KEY_D)) {
        veH = Vector2Rotate(ve, M_PIF / 2);
        player->object->position.x += veH.x;
        player->object->position.z += veH.y;
        cam->position.x += veH.x;
        cam->position.z += veH.y;
        //player->object->state = 2;
    }
    else if (IsKeyDown(KEY_A)) {
        veH = Vector2Rotate(ve, (3 * M_PIF) / 2);
        player->object->position.x += veH.x;
        player->object->position.z += veH.y;
        cam->position.x += veH.x;
        cam->position.z += veH.y;
        //player->object->state = 4;
    }
    else {
        //player->object->state = 0;
    }

    if (player->object->position.y == 0.0f)
        if (IsKeyPressed(KEY_SPACE)) player->speedY = 5;

    if (player->object->position.y >= 0.0f) {
        if (!(player->object->position.y == 0.0f && player->speedY == 0)) {
            player->object->position.y += ((player->speedY) + ((GRAVITY) * deltaTime / 2.0f)) * deltaTime;
            if (player->object->position.y < 0.0f) {
                player->object->position.y = 0.0f;
            }
            player->speedY = player->speedY + (GRAVITY * deltaTime);
        }
    }
    else {
        player->object->position.y = 0.0f;
        player->speedY = 0;
    }
}

void gravity(struct player* player) {
    float deltaTime = GetFrameTime();

    if (player->object->position.y >= 0.0f) {
        if (!(player->object->position.y == 0.0f && player->speedY == 0)) {
            player->object->position.y += ((player->speedY) + ((GRAVITY) * deltaTime / 2.0f)) * deltaTime;
            if (player->object->position.y < 0.0f) {
                player->object->position.y = 0.0f;
            }
            player->speedY = player->speedY + (GRAVITY * deltaTime);
        }
    }
    else {
        player->object->position.y = 0.0f;
        player->speedY = 0;
    }
}