#include "util.h"
#include "vector.h"

#include <stdlib.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void wrapPosition(struct Vec2* position)
{
	if (position->x > SCREEN_WIDTH)
		position->x = 0;
	else if (position->x < 0)
		position->x = SCREEN_WIDTH;

	if (position->y > SCREEN_HEIGHT)
		position->y = 0;
	else if (position->y < 0)
		position->y = SCREEN_HEIGHT;
}

int randomRangeNZ(int low, int high)
{
	int val = (random() % (high- low + 1)) + low;
	if (val == 0)
	{
		if (random() % 2 == 0)
			++val;
		else
			--val;
	}
	return val;
}
