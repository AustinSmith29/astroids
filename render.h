#include <SDL2/SDL.h>

struct Ship;
struct Bullet;
struct AstroidArray;

void drawCircle(int n_cx, int n_cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_Renderer *surface);

void drawShip(const struct Ship *ship, int radius,  SDL_Renderer *renderer);
void drawBullets(const struct Bullet *bullets, SDL_Renderer *renderer);
void drawAstroids(const struct AstroidArray *astroids, SDL_Renderer *renderer);
