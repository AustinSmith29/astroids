#include "render.h"

#include "ship.h"
#include "bullet.h"

void drawShip(const struct Ship *ship, int radius, SDL_Renderer *renderer)
{
	const Vec2 *center = getShipPosition(ship);
	Vec2 pntFront, pntLeft, pntRight, pntMid;
// I need to fix the offsets of the points. Write GetAngle for ship and go from there
	float angle = getShipAngle(ship);
	float offset = (2*3.14159) / 3;
	pntFront = createVec2(cos(angle), sin(angle)); 
	pntLeft = createVec2(cos(angle - offset), sin(angle - offset));
	pntRight = createVec2(cos(angle + offset), sin(angle + offset)); 
	pntFront = mult(&pntFront, (float)radius);
	pntLeft = mult(&pntLeft, (float)radius);
	pntRight = mult(&pntRight, (float)radius);
	pntMid = *center;
	pntFront = add(&pntFront, center);
	pntLeft = add(&pntLeft, center);
	pntRight = add(&pntRight, center);

	SDL_RenderDrawLine(renderer, pntFront.x, pntFront.y, pntLeft.x, pntLeft.y);
	SDL_RenderDrawLine(renderer, pntLeft.x, pntLeft.y,
			pntMid.x, pntMid.y);
	SDL_RenderDrawLine(renderer, pntMid.x, pntMid.y,
			pntRight.x, pntRight.y);
	SDL_RenderDrawLine(renderer, pntRight.x, pntRight.y,
			pntFront.x, pntFront.y);
}

void drawBullets(const struct Bullet *bullets, SDL_Renderer *renderer)
{
	for (int i = 0; i < MAX_BULLETS; ++i) {
		if (bullets[i].alive)
		{
			SDL_Rect rect = { 
				bullets[i].position.x,
				bullets[i].position.y, 
				4, 
				4 
			}; 
			SDL_RenderFillRect(renderer, &rect);
		}
	}
}
