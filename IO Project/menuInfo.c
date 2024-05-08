#include <raylib.h>

#include <stdlib.h>

#include "menuInfo.h"

void SetFonts(struct menuInfo *info) {
    int letters[] = U"a¹bcædeêfghijkl³mnoópqrsœtuvwxyzŸ¿A¥BCÆDEÊFGHIJKL£MNOÓPQRSŒTUVWXYZ¯";
    Font fonts[] = {
        LoadFontEx("resources/fonts/font2.ttf", 1000, letters, sizeof(letters) / sizeof(int))
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

void UnloadFonts(struct menuInfo *info) {
    int i = 0;

    while (i < info->fontsQuantity) {
        UnloadFont(info->fonts[i]);

        i += 1;
    }
    free(info->fonts);
}