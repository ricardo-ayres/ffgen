#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "geom.h"
#include "chaos.h"

Point* chaos(unsigned int iterations, unsigned int verts, int rule){
	if (verts < 3) {
		fprintf(stderr, "Can't make a polygon with less than 3 vertices!\n");
		fprintf(stderr, "Falling back to 3.\n");
		verts = 3;
	}

	srand(time(NULL));

	Point *pos = malloc(iterations*sizeof(Point));

	if (!pos) {
		fprintf(stderr, "chaos can't allocate memory!\n");
		return NULL;
	}

	/* vector pointing upwards to build polygons */
	Vector radius = { .vx = 0, .vy = 1 };
	Point center = { .x = 0.5, .y = 0.5 };
	double theta = 360.0/verts;
	/* randomize original vector orientation */
	radius = rotate_vector(radius, rand()%360);

	Point polygon[verts];
	for (int i = 0; i < verts; i++) {
		/* Set polygon vertices */
		polygon[i] = move(center, radius, 0.48);
		radius = rotate_vector(radius, theta);
	}

	int next = 0;
	int curr = rand()%verts;
	int prev = rand()%verts;
	int pf = rand()%verts;
	int cf = rand()%verts;
	for(int i=1; i<iterations; i++){
		do {
			next = rand()%verts;
		} while (!move_allowed(rule, prev, pf, curr, cf, next, verts));
		curr = next;

		pos[i] = move(pos[i-1], direction(pos[i-1], polygon[next]), 0.5);
	}
	return pos;
}

int move_allowed(
	int rule, int prev, int pf, int curr, int cf, int next, int verts
)
{
	switch(rule) {
	default:
		/* always allow */
		return 1;
	break; /* not reached */
	case 1:
		if (next == curr) {
			return 0; /* not allowed */
		} else {
			return 1; /* allowed */
		}
	break; /* not reached, guaranteed to return first */

	case 2:
		if ((curr+cf)%verts == next | (prev+pf)%verts == next) {
			return 0;
		} else {
			return 1;
		}
	break; /* not reached, guaranteed to return first */
	}
}

