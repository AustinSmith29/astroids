#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

typedef struct Vec2 {
	float x, y;
} Vec2;

Vec2 createVec2(float x, float y);
Vec2 normalize(const Vec2 *vec);
Vec2 add(const Vec2 *a, const Vec2 *b);
Vec2 sub(const Vec2 *a, const Vec2 *b);
Vec2 mult(const Vec2 *a, float c);
float dot(const Vec2 *a, const Vec2 *b);
float mag(const Vec2 *a);
#endif
