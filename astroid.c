#include "astroid.h"

#include <stdlib.h>
#include <time.h>

static const int SMALL_ASTROID_SPEED = 5;
static const int MEDIUM_ASTROID_SPEED = 3;
static const int LARGE_ASTROID_SPEED = 1;

static void set_random_astroid_start_position(struct Astroid* astroid);
static void set_random_velocity(struct Astroid* astroid);
static int is_astroid_colliding_at(int x, int y, const struct Astroid* astroid);

struct AstroidArray allocate_astroids(int nsmall, int nmedium, int nlarge)
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
			list[i].radius = 10;
			set_random_astroid_start_position(&list[i]);
			set_random_velocity(&list[i]);
			--nsmall;
		}
		else if (nmedium > 0)
		{
			list[i].type = MEDIUM;
			list[i].is_alive = 1;
			list[i].radius = 20;
			set_random_astroid_start_position(&list[i]);
			set_random_velocity(&list[i]);
			--nmedium;
		}
		else if (nlarge > 0)
		{
			list[i].type = LARGE;
			list[i].is_alive = 1;
			list[i].radius = 40;
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
		astroid->velocity.x = (random() % SMALL_ASTROID_SPEED) + 1;
		astroid->velocity.y = (random() % SMALL_ASTROID_SPEED) + 1;
		break;
	case MEDIUM:
		astroid->velocity.x = (random() % MEDIUM_ASTROID_SPEED) + 1;
		astroid->velocity.y = (random() % MEDIUM_ASTROID_SPEED) + 1;
		break;
	case LARGE:
		astroid->velocity.x = (random() % LARGE_ASTROID_SPEED) + 1;
		astroid->velocity.y = (random() % LARGE_ASTROID_SPEED) + 1;
		break;
	case DUMMY:
		break;
	}
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

void explode_astroid(int id, const struct AstroidArray* list)
{
}

void deallocate_astroids(struct AstroidArray* astroids)
{
	free(astroids->array);
}
