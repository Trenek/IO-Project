#include <raylib.h>

#include <stdlib.h>

#include "state.h"

static void SetFonts(struct menuInfo *info) {
    int letters[] = U"?!,.a¹bcædeêfghijkl³mnoópqrsœtuvwxyzŸ¿A¥BCÆDEÊFGHIJKL£MNOÓPQRSŒTUVWXYZ¯";
    Font fonts[] = {
        LoadFontEx("resources/fonts/font2.ttf", 100, letters, sizeof(letters) / sizeof(int))
    };    
    int i = 0;

    info->fontsQuantity = sizeof(fonts) / sizeof(Font);
    info->fonts = malloc(sizeof(fonts));

    while (i < info->fontsQuantity) {
        info->fonts[i] = fonts[i];
        GenTextureMipmaps(&info->fonts[i].texture);
        SetTextureFilter(info->fonts[i].texture, TEXTURE_FILTER_POINT);

        i += 1;
    }
}

static void UnloadFonts(struct menuInfo *info) {
    int i = 0;

    while (i < info->fontsQuantity) {
        UnloadFont(info->fonts[i]);

        i += 1;
    }
    free(info->fonts);
}

static void loadMusic(struct menuInfo *info) {
    InitAudioDevice();

    Music music[] = {
        LoadMusicStream("resources/music/music1.mp3"),
        LoadMusicStream("resources/music/music2.mp3")
    };
    int i = 0;

    info->music = malloc(sizeof(music));
    info->musicQuantity = sizeof(music) / sizeof(Music);
    while (i < info->musicQuantity) {
        info->music[i] = music[i];
        i += 1;
    }

    i = 0;
    while (i < info->musicQuantity) {
        PlayMusicStream(info->music[i]);
        i += 1;
    }
}

static void unloadMusic(struct menuInfo *info) {
    int i = 0;

    while (i < info->musicQuantity) {
        UnloadMusicStream(info->music[i]);
        i += 1;
    }

    CloseAudioDevice();
    free(info->music);
}

void initializeState(struct menuInfo *info) {
    SetFonts(info);
    loadMusic(info);
}

void freeState(struct menuInfo *info) {
    UnloadFonts(info);
    unloadMusic(info);
}