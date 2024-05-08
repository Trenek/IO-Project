struct menuInfo {
	Font *fonts;
	int fontsQuantity;
	const char *saveName;
};

void SetFonts(struct menuInfo *info);
void UnloadFonts(struct menuInfo *info);