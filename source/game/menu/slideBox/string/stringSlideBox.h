#define SLIDEBOX_H

#include <raylib.h>

struct slideBoxPositionParameters {
    int x;
    int y;
    int incX;
    int incY;
    int posX;
    int posY;
    int width;
};

struct slideBox {
    int numberOfOptions;
    bool isActive;
    int currentOption;

    union {
        struct slideBoxPositionParameters init;
        struct {
            Rectangle rect[3];
            float incY;
        };
    };

    Font *font;
    int fontSize;
    Color fontColor;
    Color color;
    Color borderActiveColor;
    Color borderColor;
    int spaceing;
    const char **options;
};

void CalculateSlideBoxPosition(struct slideBox *element);
void DrawSlideBox(const struct slideBox *element);
void InternalUpdateSlideBox(struct slideBox *element);

inline void UpdateSlideBox(struct slideBox *element) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        element->isActive = CheckCollisionPointRec(GetMousePosition(), element->rect[0]);
    }

    if (element->isActive) InternalUpdateSlideBox(element);
}