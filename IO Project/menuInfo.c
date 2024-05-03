#include <raylib.h>

#include "menuInfo.h"

void SetFontsFilter(Font fonts[], int size) {
    int i = 0;

    while (i < size) {
        GenTextureMipmaps(&fonts[i].texture);
        SetTextureFilter(fonts[i].texture, TEXTURE_FILTER_POINT);

        i += 1;
    }
}

void UnloadFonts(Font fonts[], int size) {
    int i = 0;

    while (i < size) {
        UnloadFont(fonts[i]);

        i += 1;
    }
}