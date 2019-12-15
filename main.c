#include "ship.h"
#include "bullet.h"
#include "astroid.h"
#include "render.h"

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

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
	struct AstroidArray astroidArray = allocateAstroids(0, 0, 3);
	int quit = 0;
	SDL_Event e;
	const Uint32 FPS = 60;
	int rValue = 255;

	while (!quit)
	{
		Uint32 ticks = SDL_GetTicks();
		while( SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT) {
				quit = 1;
			}
			else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym)
				{
					case SDLK_SPACE:
						createBullet(shipBullets,
							&ship->position,
							&ship->direction);	
				}
			}
		}

		const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);
		if (keyboard_state[SDL_SCANCODE_UP])
			shipAccelerate(ship);
		if (keyboard_state[SDL_SCANCODE_RIGHT])
			shipRotateRight(ship);
		else if (keyboard_state[SDL_SCANCODE_LEFT])
			shipRotateLeft(ship);

		shipMove(ship, 1.0f);
		updateBullets(shipBullets);
		updateAstroids(&astroidArray);

		if (getAstroidCollidingAt(ship->position.x, ship->position.y, 16, &astroidArray) >= 0)
		{
			rValue = 0;
		}
		else
		{
			rValue = 255;
		}
		//Clear Screen
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		drawShip(ship, 16, renderer);
		drawCircle(ship->position.x, ship->position.y, 16, rValue, 255, 255, 255, renderer);
		drawBullets(shipBullets, renderer);
		drawAstroids(&astroidArray, renderer);
		SDL_RenderPresent(renderer);

		Uint32 time = SDL_GetTicks() - ticks;
		if (time < (1000 / FPS))
			SDL_Delay((1000 / FPS) - time);
	}
	destroyShip(ship);
	deallocateAstroids(&astroidArray);
	SDL_Quit();
	return 0;
}
