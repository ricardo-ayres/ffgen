#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "ff.h"


int main() {
	int width = 640;
	int height = 480;

	FarbFeld *picture = FF_init(width, height);

	FF_write(picture);
	
	return 0;
}
