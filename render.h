#include <SDL2/SDL.h>
#include <stdlib.h>

struct Ship;
struct Bullet;
void drawBullets(const struct Bullet *bullets, SDL_Renderer *renderer);
void drawShip(const struct Ship *ship, int radius,  SDL_Renderer *renderer);

