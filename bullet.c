#include "bullet.h"

static void updateBullet(struct Bullet *bullet);

void createBullet(struct Bullet *list, const Vec2 *pos, const Vec2 *dir)
{
	int i;
	for (i=0; i < MAX_BULLETS; i++) {
		if (!list[i].alive) {
			struct Bullet bullet;
		       	bullet.position = *pos;
			bullet.velocity = mult(dir, (float)SPEED);
			bullet.alive = 1;
			bullet.distance = 0;
			list[i] = bullet;	
		}
	}
}

void updateBullets(struct Bullet *list) {
	int i;
	for (i=0; i < MAX_BULLETS; i++) {
		if (!list[i].alive)
			continue;
		updateBullet(&(list[i]));
	}
}

void updateBullet(struct Bullet *bullet)
{
	if (bullet->alive) {
		bullet->position = add(&bullet->position, &bullet->velocity);
		bullet->distance++;
	}
	if (bullet->distance >= MAX_DISTANCE) {
		bullet->alive = 0;
	}

	if (bullet->position.x > 640)
		bullet->position.x = 0;
	if (bullet->position.x < 0)
		bullet->position.x = 640;
	if (bullet->position.y < 0)
		bullet->position.y = 480;
	if (bullet->position.y > 480)
		bullet->position.y = 0;
}
