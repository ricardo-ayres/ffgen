#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "geom.h"
#include "sierp.h"

Point* sierp(int iterations){
	srand(time(NULL));

	Point *pos = malloc(iterations*sizeof(Point));

	if (!pos) {
		fprintf(stderr, "sierp can't allocate memory!\n");
		return NULL;
	}
	
	Point p1;
	p1.x = 0;
	p1.y = 0;

	Point p2;
	p2.x = 0.5;
	p2.y = 1.0;

	Point p3;
	p3.x = 1;
	p3.y = 0;

	Point triangle[3] = {p1, p2, p3};

	pos[0].x = p1.x;
	pos[0].y = p1.y;
	int next;

	for(int i=1; i<iterations; i++){
		next = rand()%3;
		pos[i] = move(pos[i-1], direction(pos[i-1], triangle[next]), 0.5);
	}
	return pos;
}






