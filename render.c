#include "render.h"

#include "ship.h"
#include "bullet.h"
#include "astroid.h"

/* 
 * Thank you github user derofim for the code to draw circles.
*/
static void set_pixel(SDL_Renderer *rend, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(rend, r,g,b,a);
	SDL_RenderDrawPoint(rend, x, y);
}

void drawCircle(int n_cx, int n_cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_Renderer *surface)
{
	// if the first pixel in the screen is represented by (0,0) (which is in sdl)
	// remember that the beginning of the circle is not in the middle of the pixel
	// but to the left-top from it:

	double error = (double)-radius;
	double x = (double)radius - 0.5;
	double y = (double)0.5;
	double cx = n_cx - 0.5;
	double cy = n_cy - 0.5;

	while (x >= y)
	{
		set_pixel(surface, (int)(cx + x), (int)(cy + y), r, g, b, a);
		set_pixel(surface, (int)(cx + y), (int)(cy + x), r, g, b, a);

		if (x != 0)
		{
			set_pixel(surface, (int)(cx - x), (int)(cy + y), r, g, b, a);
			set_pixel(surface, (int)(cx + y), (int)(cy - x), r, g, b, a);
		}

		if (y != 0)
		{
			set_pixel(surface, (int)(cx + x), (int)(cy - y), r, g, b, a);
			set_pixel(surface, (int)(cx - y), (int)(cy + x), r, g, b, a);
		}

		if (x != 0 && y != 0)
		{
			set_pixel(surface, (int)(cx - x), (int)(cy - y), r, g, b, a);
			set_pixel(surface, (int)(cx - y), (int)(cy - x), r, g, b, a);
		}

		error += y;
		++y;
		error += y;

		if (error >= 0)
		{
			--x;
			error -= x;
			error -= x;
		}
	}
}

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

void drawAstroids(const struct AstroidArray *astroids, SDL_Renderer *renderer)
{
	for (int i = 0; i < astroids->length; ++i) {
		const struct Astroid* astroid = &(astroids->array[i]);
		if (astroid->is_alive)
		{
			drawCircle(astroid->position.x,
				   astroid->position.y,
				   astroid->radius,
				   255, 255, 255, 255,
				   renderer);
		}
	}
}
