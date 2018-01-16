#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "geom.h"
#include "ff.h"
#include "sierp.h"


int main() {
	int width = 640;
	int height = 480;

	FarbFeld *picture = FF_init(width, height);

	int n = 1000;
	Point *pos = malloc(n*sizeof(Point));
	if (!pos) {
		fprintf(stderr, "ffgen: oops, can't allocate pos!\n");
	}

	pos = sierp(n);
	
	FF_plot_pos(picture, pos, n);

	FF_write(picture);
	
	return 0;
}
