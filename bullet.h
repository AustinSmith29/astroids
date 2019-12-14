#ifndef BULLET_H
#define BULLET_H

#include "vector.h"

#define MAX_BULLETS 10
#define MAX_DISTANCE 75
#define SPEED 5.f	

struct Bullet {
	Vec2 position;
	Vec2 velocity;
	int distance;	// how far bullet has gone	
	int alive;
};

void createBullet(struct Bullet *list, const Vec2 *pos, const Vec2 *direction);
void updateBullets(struct Bullet *list);
#endif
