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
};

void nCalculateSlideBoxPosition(struct slideBox *element);
void nDrawSlideBox(const struct slideBox *element);
void nInternalUpdateSlideBox(struct slideBox *element);

inline void CalculateSlideBoxPosition(struct slideBox *element) {
    nCalculateSlideBoxPosition(element);
}
inline void DrawSlideBox(const struct slideBox *element) {
    nDrawSlideBox(element);
}
inline void InternalUpdateSlideBox(struct slideBox *element) {
    nInternalUpdateSlideBox(element);
}

inline void UpdateSlideBox(struct slideBox *element) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        element->isActive = CheckCollisionPointRec(GetMousePosition(), element->rect[0]);
    }

    if (element->isActive) InternalUpdateSlideBox(element);
}