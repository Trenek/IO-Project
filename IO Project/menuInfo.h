struct menuInfo {
	Font *fonts;
	const char *saveName;
};

void SetFontsFilter(Font fonts[], int size);
void UnloadFonts(Font fonts[], int size);