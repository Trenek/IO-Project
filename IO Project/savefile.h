#include <stdbool.h>

struct playInfo;

bool createNewSave(const char *const saveName, const char *const characterName, const int bodyParts[10], const int armorParts[9]);
void loadSaveFile(struct playInfo *this, const char *saveName);
void unloadSaveFile(struct playInfo *this);
void saveSaveFile(struct playInfo *this, const char *saveName);