#include "inputBox.h"

#define MAX_INPUT_CHARS 30

void DrawInputBox(struct inputBox* element) {
    Vector2 size = MeasureTextEx(*(element->font), element->text, (float)element->fontSize, (float)element->spaceing);
    int y = element->y - (int)(size.y / 2) - element->incY;
    int width = (int)size.x + (element->incX << 1);
    int height = (int)size.y + (element->incY << 1);
    Rectangle rec = { (float)element->x, (float)y, (float)width, (float)height };

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
        element->isActive = CheckCollisionPointRec(GetMousePosition(), rec);
    
    DrawRectangleRec(rec, element->color);
    DrawRectangleLines(element->x, y, width, height,  
        element->isActive ? 
        element->borderActiveColor : 
        element->borderColor
    );
    DrawTextEx(*(element->font), element->text, (Vector2) {.x = (float)element->x + element->incX, .y = (float)element->y - size.y / 2.0f }, (float)element->fontSize, (float)element->spaceing, element->fontColor);

    if (element->isActive) updateInputBox(element);
}

int updateInputBox(struct inputBox* element) {
    // Get char pressed
    int key = GetCharPressed();

    // Check if more characters have been pressed on the same frame
    while (key > 0) {
        if ((key >= 32) && (key <= 125) && (element->currentLength < MAX_INPUT_CHARS)) {
            element->text[element->currentLength] = (char)key;
            element->text[element->currentLength+1] = '\0'; // Add null terminator at the end of the string.
            element->currentLength++;
        }

        key = GetCharPressed();  // Check next character in the queue
    }

    if (IsKeyPressed(KEY_BACKSPACE)) {
        element->currentLength--;
        if (element->currentLength < 0) element->currentLength = 0;
        element->text[element->currentLength] = '\0';
    }

    return 0;
}