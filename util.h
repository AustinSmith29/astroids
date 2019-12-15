#ifndef _UTIL_H__
#define _UTIL_H__

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

struct Vec2;
void wrapPosition(struct Vec2* position);
int max(int a, int b);
// Returns a number within range that is not zero
int randomRangeNZ(int low, int high);
int isCollision(const struct Vec2* aPos,
		int aRadius,
		const struct Vec2* bPos,
		int bRadius);
#endif
