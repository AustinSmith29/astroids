#ifndef SHIP_H__
#define SHIP_H__

#include "vector.h"

struct Ship {
	Vec2 position;
	Vec2 acceleration;
	Vec2 velocity;
	Vec2 direction;
};

struct Ship *createShip();
void destroyShip(struct Ship* ship);
void shipRotateRight(struct Ship *ship);
void shipRotateLeft(struct Ship *ship);
void shipAccelerate(struct Ship *ship);
void shipMove(struct Ship *ship, float deltatime);
const Vec2 *getShipDirection(const struct Ship *ship);
const Vec2 *getShipPosition(const struct Ship *ship);
float getShipAngle(const struct Ship *ship);
void setShipPosition(struct Ship *ship, float x, float y);
#endif
