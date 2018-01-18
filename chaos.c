#include <stdlib.h>
#include <stdio.h>

#include "geom.h"
#include "chaos.h"

Point*
chaos(unsigned int iterations, unsigned int seed)
{
	srand(seed);

	Point *pos = calloc(iterations, sizeof(Point));

	if (!pos) {
		fprintf(stderr, "chaos can't allocate memory!\n");
		return NULL;
	}

	int verts = 3 + (rand()%4); /* from 3 up to 6 */
	fprintf(stderr, "chaos: [%d-gon] ", verts);

		/* vector pointing upwards to build polygons */
	Vector radius = { .vx = 0, .vy = 1 };
	Point center = { .x = 0.5, .y = 0.5 };
	double theta = 360.0/verts;
	/* randomize original vector orientation */
	radius = rotate_vector(radius, rand()%360);

	Point polygon[verts];
	for (int i = 0; i < verts; i++) {
		/* Set polygon vertices */
		polygon[i] = move(center, radius, 0.5);
		radius = rotate_vector(radius, theta);
	}

	/* randomize scale of movement within known good values */
	/*
	double scales[4] = {1.0/3.0, 3.0/8.0, 1.0/2.0, 2.0/3.0};
	double scale = scales[rand()%4];
	*/
	int numerator = 1+rand()%9;
	int denominator = 1+numerator+rand()%9;
	double scale = (double) numerator/(double) denominator;

	fprintf(stderr, "[scale %d/%d] ", numerator, denominator);


	int rule = rand()%4;
	fprintf(stderr, "[rule %d] ", rule);

	int pf = rand()%verts;
	int cf = rand()%verts;
	if (rule == 2) {
		fprintf(stderr, "(cf %d) (pf %d)", cf, pf);
	}
	fprintf(stderr, "\n");
	int next = 0;
	int curr = rand()%verts;
	int prev = rand()%verts;
	for(int i=1; i<iterations; i++){
		do {
			next = rand()%verts;
		} while (!move_allowed(rule, prev, pf, curr, cf, next, verts));
		curr = next;

		pos[i] = move(pos[i-1], direction(pos[i-1], polygon[next]), scale);
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
		if ((prev+pf)%verts == next) {
			return 0;
		} /* else: fallthrough */

	case 3:
		if ((curr+cf)%verts == next) {
			return 0;
		} else {
			return 1;
		}
	break; /* not reached, guaranteed to return first */
	}
}

