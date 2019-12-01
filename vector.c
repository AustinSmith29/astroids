#include "vector.h"

Vec2 createVec2(float x, float y)
{
	Vec2 v;
	v.x = x;
	v.y = y;
	return v;
}

Vec2 normalize(const Vec2 *vec)
{
	float m = mag(vec);
	float x = vec->x / m;
	float y = vec->y / m;
	Vec2 norm = createVec2(x, y);
	return norm;
}	

Vec2 add(const Vec2 *a, const Vec2 *b)
{
	Vec2 v = createVec2( (a->x + b->x), (a->y + b->y) );
	return v;
}

Vec2 sub(const Vec2 *a, const Vec2 *b)
{
	Vec2 v = createVec2( (a->x - b->x), (a->y - b->y) );
	return v;
}

Vec2 mult(const Vec2 *a, float scalar)
{
	Vec2 v = createVec2( (a->x * scalar), (a->y * scalar) );
	return v;
}

float dot(const Vec2 *a, const Vec2 *b)
{
	return (a->x * b->x) + (a->y * b->y);
}

float mag(const Vec2 *a)
{
	return sqrt( pow(a->x, 2) + pow(a->y, 2) );
}
