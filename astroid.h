#ifndef ASTROID_H__
#define ASTROID_H__

#include "vector.h"


struct Astroid
{
	int id;
	int is_alive;
	int radius;
	enum _type {DUMMY, SMALL, MEDIUM, LARGE} type;
	Vec2 position;
	Vec2 velocity;
};

struct AstroidArray
{
	struct Astroid* array;
	int length;
};

struct AstroidArray allocate_astroids(int nsmall, int nmedium, int nlarge);
int get_astroid_colliding_at(int x, int y, const struct AstroidArray* astroids);
void explode_astroid(int id, const struct AstroidArray* astroids);
void deallocate_astroids(struct AstroidArray* astroids);

#endif
