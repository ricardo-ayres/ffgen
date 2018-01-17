#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

#include "geom.h"
#include "ff.h"
#include "chaos.h"


int main() {
	/* unsigned char *seed = malloc(sizeof(char));
	fgets(seed, sizeof(int), stdin);
	srand((unsigned int) *seed);
	*/

	srand(time(NULL));

	int width = 1440;
	int height = 900;
	if (width < 1 | height < 1) {
		fprintf(stderr, "Picture dimension can't be zero or negative!\n");
		exit(1);
	}

	FarbFeld *picture = FF_init(width, height);

	int n = 1000000;
	Point *pos = malloc(n*sizeof(Point));
	if (!pos) {
		fprintf(stderr, "ffgen: oops, can't allocate pos!\n");
	}

	int verts = 3 + (rand()%5); /* verts in [3,7] */
	int rule = rand()%3;
	pos = chaos(n, verts, rule);
	
	FF_plot_pos(picture, pos, n);

	FF_write(picture);
	
	return 0;
}
