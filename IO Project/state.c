#include <raylib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "state.h"

static void initializePlayer(struct menuInfo *info) {
    memset(info->body, 0, 10 * sizeof(int));
}

void initializeState(struct menuInfo *info) {
    loadResources(&info->resources);
    initializePlayer(info);
}

void freeState(struct menuInfo *info) {
    unloadResources(&info->resources);
}