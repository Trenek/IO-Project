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
    const char *options[];
};

void sCalculateSlideBoxPosition(struct slideBox *element);
void sDrawSlideBox(const struct slideBox *element);
void sInternalUpdateSlideBox(struct slideBox *element);

inline void CalculateSlideBoxPosition(struct slideBox *element) {
    sCalculateSlideBoxPosition(element);
}
inline void DrawSlideBox(const struct slideBox *element) {
    sDrawSlideBox(element);
}
inline void InternalUpdateSlideBox(struct slideBox *element) {
    sInternalUpdateSlideBox(element);
}

inline void UpdateSlideBox(struct slideBox *element) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        element->isActive = CheckCollisionPointRec(GetMousePosition(), element->rect[0]);
    }

    if (element->isActive) InternalUpdateSlideBox(element);
}