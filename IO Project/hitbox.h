struct playInfo;
enum playState;

void detectFight(struct playInfo *info, enum playState *state);
void hitbox(struct playInfo *info);
void findShop(struct playInfo *info);
void hitboxShop(struct playInfo *info, int *shop);
void followPlayer(struct playInfo *info);