#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/random.h>

#include "geom.h"
#include "ff.h"
#include "chaos.h"


int main() {
	unsigned int seed = 0;
	getrandom(&seed, sizeof(int), 0);
	fprintf(stderr, "main seed:  %010u\n", seed);
	srand(seed);

	int width = 1024;
	int height = 768;
	if (width < 1 | height < 1) {
		fprintf(stderr, "Picture dimension can't be zero or negative!\n");
		exit(1);
	}

	FarbFeld *picture = FF_init(width, height);

	int n = 1000000;
	getrandom(&seed, sizeof(int), 0);
	fprintf(stderr, "chaos seed: %010u\n", seed);
	Point *pos = NULL;
	pos = chaos(n, seed);

	FF_plot_pos(picture, pos, n);
	FF_write(picture);

	/* cleanup */
	free(pos);
	FF_destroy(picture);
	
	return 0;
}
