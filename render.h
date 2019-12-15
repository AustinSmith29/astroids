#include <SDL2/SDL.h>

struct Ship;
struct Bullet;
struct AstroidArray;
void drawShip(const struct Ship *ship, int radius,  SDL_Renderer *renderer);
void drawBullets(const struct Bullet *bullets, SDL_Renderer *renderer);
void drawAstroids(const struct AstroidArray *astroids, SDL_Renderer *renderer);
