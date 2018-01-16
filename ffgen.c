#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "geom.h"
#include "ff.h"
#include "sierp.h"


int main() {
	int width = 1440;
	int height = 900;

	FarbFeld *picture = FF_init(width, height);

	int n = 10000;
	Point *pos = malloc(n*sizeof(Point));
	if (!pos) {
		fprintf(stderr, "ffgen: oops, can't allocate pos!\n");
	}

	pos = sierp(n);
	
	FF_plot_pos(picture, pos, n);

	FF_write(picture);
	
	return 0;
}
