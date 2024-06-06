struct saveData {
    char *text;
    unsigned short year : 12;
    unsigned short month : 4;
    unsigned short day : 5;
    unsigned short hour : 5;
    unsigned short minute : 6;
    unsigned short second : 6;
};

void initializeSaveData(struct saveData *const this, const char *const savePath);
void freeSaveData(struct saveData *const this);

int cmpSaveData(const struct saveData *const arg1, const struct saveData *const arg2);

inline const char *assembleDate(const struct saveData *const this) {
    return TextFormat("%02hu:%02hu %02hu/%02hu/%hu", this->hour, this->minute, this->day, this->month, this->year);
}