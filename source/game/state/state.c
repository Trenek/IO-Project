#include <string.h>

#include <raylib.h>

#include "state.h"

static void InitializePlayer(struct menuInfo *info) {
    memset(info->body, 0, 10 * sizeof(int));
}

void initializeState(struct menuInfo *info) {
    LoadResources(&info->resources);
    InitializePlayer(info);
}

void freeState(struct menuInfo *info) {
    UnloadResources(&info->resources);
}