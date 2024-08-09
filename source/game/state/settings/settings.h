struct menuInfo;
struct Settings {
    int framesPerSecond;
    int textureQuality;
    int windowWidth;
    int windowHeight;
    int fullScreenMode;
};

void loadSettings(struct menuInfo *info);