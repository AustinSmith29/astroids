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

struct AstroidArray allocateAstroids(int nsmall, int nmedium, int nlarge);
int getAstroidCollidingAt(int x, int y, const struct AstroidArray* astroids);
void explodeAstroid(int id, const struct AstroidArray* astroids);
void updateAstroids(const struct AstroidArray* astroids);
void deallocateAstroids(struct AstroidArray* astroids);

#endif
