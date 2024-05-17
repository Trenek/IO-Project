#include "equipementBox.h"


void DrawEquipementBox(struct equipementBox element) {
    DrawRectangle(element.x, element.y, element.width, element.height, GRAY);
    for (int i = 0; i < 25; i++) {
        element.items[i].isActive = i == element.activeItem;
        DrawItemBox(element.items[i]);
    }
    for (int i = 0; i < 7; i++) {
        element.itemTypes[i].isActive = i == element.activeItemType;
        DrawItemBox(element.itemTypes[i]);
    }
}