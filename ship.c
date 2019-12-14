#include "ship.h"

#include <math.h>
#include <stdlib.h>

static const float ROTATE_INC = 3.14159f/12.f;
static const float ACCELERATE = 0.1f;
static const float MAX_SPEED = 7.0f;

struct Ship *createShip()
{
	struct Ship *ship = malloc(sizeof(struct Ship));
	setShipPosition(ship, 0.f, 0.f);
	ship->velocity.x = ship->velocity.y = 0.f;
	ship->acceleration.x = ship->acceleration.y = 0.f;
	ship->direction.x = ship->direction.y = 0.f;
	return ship;
}

void destroyShip(struct Ship* ship)
{
	free(ship);
	ship = NULL;
}

void shipRotateRight(struct Ship *ship)
{	
	float angle = atan2(ship->direction.y, ship->direction.x);
	ship->direction.x = cos(angle + ROTATE_INC);
	ship->direction.y = sin(angle + ROTATE_INC);	
}

void shipRotateLeft(struct Ship *ship)
{
	float angle = atan2(ship->direction.y, ship->direction.x);
	ship->direction.x = cos(angle - ROTATE_INC);
	ship->direction.y = sin(angle - ROTATE_INC);
}

void shipAccelerate(struct Ship *ship)
{
	ship->acceleration.x += ship->direction.x * ACCELERATE;
	ship->acceleration.y += ship->direction.y * ACCELERATE;	
}

void shipMove(struct Ship *ship, float deltatime)
{
	ship->velocity = add(&ship->acceleration, &ship->velocity);
	float velocityMag = mag(&(ship->velocity));
	if (velocityMag >= MAX_SPEED) {
		ship->velocity = sub(&ship->velocity, &ship->acceleration);
	}
	ship->position = add(&ship->position, &ship->velocity);
	ship->position = mult(&ship->position, deltatime);
	ship->velocity = mult(&ship->velocity, deltatime);
	ship->acceleration = createVec2(0.0f, 0.0f);
	if (ship->position.x > 640)
		setShipPosition(ship, 0, ship->position.y);
	if (ship->position.x < 0)
		setShipPosition(ship, 640, ship->position.y);
	if (ship->position.y < 0)
		setShipPosition(ship, ship->position.x, 480);
	if (ship->position.y > 480)
		setShipPosition(ship, ship->position.x, 0);
}

const Vec2 *getShipDirection(const struct Ship *ship)
{
	const Vec2 *pVec = &ship->direction;
	return pVec;
}

const Vec2 *getShipPosition(const struct Ship *ship)
{
	const Vec2 *pVec = &ship->position;
	return pVec;
}

float getShipAngle(const struct Ship *ship)
{
	return atan2(ship->direction.y, ship->direction.x);
}

void setShipPosition(struct Ship *ship, float x, float y)
{
	ship->position.x = x;
	ship->position.y = y;
}
