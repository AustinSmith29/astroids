#include "astroid.h"
#include "util.h"

#include <stdlib.h>
#include <time.h>

static const int SMALL_ASTROID_SPEED = 5;
static const int MEDIUM_ASTROID_SPEED = 3;
static const int LARGE_ASTROID_SPEED = 1;

static void set_random_astroid_start_position(struct Astroid* astroid);
static void set_random_velocity(struct Astroid* astroid);
static int is_astroid_colliding_at(int x, int y, const struct Astroid* astroid);
static Vec2 random_velocity(int max_component);

struct AstroidArray allocateAstroids(int nsmall, int nmedium, int nlarge)
{
	// Large astroids become medium astroids which become small astroids.
	// 1 large becomes 2 medium and 1 medium becomes 3 small.
	// We allocate a single buffer based on how many small astroids there
	// will be after medium and large astroids are destroyed.
	srand(time(0)); // for random position and velocity
	int total_small = nsmall + nmedium * 3 + nlarge * 6;
	struct Astroid* list = malloc(sizeof(struct Astroid) * total_small);
	for (int i = 0; i < total_small; ++i)
	{
		list[i].id = i;
		if (nsmall > 0)
		{
			list[i].type = SMALL;
			list[i].is_alive = 1;
			list[i].radius = 20;
			set_random_astroid_start_position(&list[i]);
			set_random_velocity(&list[i]);
			--nsmall;
		}
		else if (nmedium > 0)
		{
			list[i].type = MEDIUM;
			list[i].is_alive = 1;
			list[i].radius = 40;
			set_random_astroid_start_position(&list[i]);
			set_random_velocity(&list[i]);
			--nmedium;
		}
		else if (nlarge > 0)
		{
			list[i].type = LARGE;
			list[i].is_alive = 1;
			list[i].radius = 80;
			set_random_astroid_start_position(&list[i]);
			set_random_velocity(&list[i]);
			--nlarge;
		}
		else 
		{
			list[i].type = DUMMY;
			list[i].is_alive = 0; 
			list[i].radius = 0;
		}
	}
	struct AstroidArray array = { list, total_small };
	return array;
}

static void set_random_astroid_start_position(struct Astroid* astroid)
{
	// Assumes the player starts in the middle of the screen.
	do {
		astroid->position.x = random() % 640;
		astroid->position.y = random() % 480;
	} while (is_astroid_colliding_at(640/2, 480/2, astroid));
}

static void set_random_velocity(struct Astroid* astroid)
{
	switch(astroid->type)
	{
	case SMALL:
		astroid->velocity = random_velocity(SMALL_ASTROID_SPEED); 
		break;
	case MEDIUM:
		astroid->velocity = random_velocity(MEDIUM_ASTROID_SPEED); 
		break;
	case LARGE:
		astroid->velocity = random_velocity(LARGE_ASTROID_SPEED); 
		break;
	case DUMMY:
		break;
	}
}

Vec2 random_velocity(int max_component)
{
	Vec2 vec;
	vec.x = randomRangeNZ(-max_component, max_component);	
	vec.y = randomRangeNZ(-max_component, max_component);	
	return vec;
}

int get_astroid_colliding_at(int x, int y, const struct AstroidArray* array)
{
	return 0;
}

// TODO: Implement this
int is_astroid_colliding_at(int x, int y, const struct Astroid* astroid)
{
	return 0;
}

void explodeAstroid(int id, const struct AstroidArray* list)
{
}

void updateAstroids(const struct AstroidArray* astroids)
{
	for (int i = 0; i < astroids->length; ++i) {
		if (astroids->array[i].is_alive)
			astroids->array[i].position.x += astroids->array[i].velocity.x;
			astroids->array[i].position.y += astroids->array[i].velocity.y;
			wrapPosition(&(astroids->array[i].position));
	}
}

void deallocateAstroids(struct AstroidArray* astroids)
{
	free(astroids->array);
}
