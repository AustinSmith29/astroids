#include "ship.h"
#include "bullet.h"
#include "render.h"

#include <SDL2/SDL.h>
#include <stdlib.h>

int main()
{
	SDL_Window *window = SDL_CreateWindow("Astroids",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			640, 480, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED);

	struct Ship *ship = createShip();
	ship->position = createVec2(320.0f, 240.0f);
	ship->direction = createVec2(0.0f, 1.0f);
	struct Bullet shipBullets[MAX_BULLETS];
	int quit = 0;
	SDL_Event e;
	while (!quit)
	{
		while( SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT) {
				quit = 1;
			}
			else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym)
				{
					case SDLK_UP:
						shipAccelerate(ship);
						break;
					case SDLK_RIGHT:
						shipRotateRight(ship);
						break;
					case SDLK_LEFT:
						shipRotateLeft(ship);
						break;
					case SDLK_SPACE:
						createBullet(shipBullets,
							&ship->position,
							&ship->direction);	
				}
			}
		}
		shipMove(ship, 1.0f);
		updateBullets(shipBullets);
		//Clear Screen
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		drawShip(ship, 16, renderer);
		drawBullets(shipBullets, renderer);
		SDL_RenderPresent(renderer);
	}
	destroyShip(ship);
	SDL_Quit();
	return 0;
}
