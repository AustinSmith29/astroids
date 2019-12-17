#include "astroid.h"
#include "util.h"

#include <stdlib.h>
#include <time.h>
#include <string.h>

static const int SMALL_ASTROID_SPEED = 5;
static const int MEDIUM_ASTROID_SPEED = 3;
static const int LARGE_ASTROID_SPEED = 1;

static const int SMALL_IN_MEDIUM = 3;
static const int SMALL_IN_LARGE = 6;

static void init_astroid(Vec2* position, int type, struct Astroid* astroid);
static Vec2 get_random_astroid_start_position();
static void set_random_velocity(struct Astroid* astroid);
static int is_astroid_colliding_at(int x, int y, int radius, const struct Astroid* astroid);
static Vec2 random_velocity(int max_component);
static int firstFreeIndex(const struct AstroidArray* astroids);


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
		Vec2 position = get_random_astroid_start_position();
		if (nsmall > 0)
		{
			init_astroid(&position, SMALL, &list[i]);
			--nsmall;
		}
		else if (nmedium > 0)
		{
			init_astroid(&position, MEDIUM, &list[i]);
			--nmedium;
		}
		else if (nlarge > 0)
		{
			init_astroid(&position, LARGE, &list[i]);
			--nlarge;
		}
		else 
		{
			init_astroid(&position, DUMMY, &list[i]);
		}
	}
	struct AstroidArray array = { list, total_small };
	return array;
}

static void init_astroid(Vec2* position, int type, struct Astroid* astroid)
{
	memset(astroid, 0, sizeof(struct Astroid));
	astroid->position = *position;
	astroid->type = type;
	astroid->is_alive = 1;
	set_random_velocity(astroid);
	switch (type)
	{
		case SMALL:
			astroid->radius = 20;
			break;
		case MEDIUM:
			astroid->radius = 40;
			break;
		case LARGE:
			astroid->radius = 80;
			break;
		case DUMMY:
			astroid->radius = 0;
			astroid->is_alive = 0;
			break;
	}

}

static Vec2 get_random_astroid_start_position()
{
	Vec2 playerZoneCenter = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
	Vec2 position;
	// Assumes the player starts in the middle of the screen.
	do {
		position.x = random() % SCREEN_WIDTH;
		position.y = random() % SCREEN_HEIGHT;
	} while (isCollision(&playerZoneCenter, 64, &position, 80));
	return position;
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

int getAstroidCollidingAt(int x, int y, int radius, const struct AstroidArray* array)
{
	for (int i = 0; i < array->length; ++i) {
		if (array->array[i].is_alive && 
		    is_astroid_colliding_at(x, y, radius, &(array->array[i])))
			return i;
	}
	return -1;
}

int is_astroid_colliding_at(int x, int y, int radius, const struct Astroid* astroid)
{
	Vec2 point = {x, y};
	return isCollision(&point, radius, &astroid->position, astroid->radius);	
}

static int firstFreeIndex(const struct AstroidArray* astroids)
{
	for (int i = 0; i < astroids->length; ++i) {
		if (astroids->array[i].type == DUMMY) {
			return i;
		}
	}
	return -1;
}

void explodeAstroid(int id, struct AstroidArray* list)
{
	struct Astroid* astroid = &(list->array[id]);
	astroid->is_alive = 0;
	switch(astroid->type)
	{
		case DUMMY:
		case SMALL:
			break;
		case MEDIUM:
			for (int i = 0; i < 3; ++i)
			{
				int index = firstFreeIndex(list);
				init_astroid(&astroid->position, SMALL, &list->array[index]);
			}
			break;
		case LARGE:
			for (int i = 0; i < 2; ++i)
			{
				int index = firstFreeIndex(list);
				init_astroid(&astroid->position, MEDIUM, &list->array[index]);
			}
			break;
	}
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
