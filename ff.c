#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <byteswap.h>

#include "geom.h"
#include "ff.h"

/* Return a pointer to a picture with given dimensions */
FarbFeld* FF_init(uint32_t width, uint32_t height) {
	FarbFeld *picture = malloc(sizeof(FarbFeld));
	if (!picture) {
		fprintf(stderr, "FF_init failed to allocate memory!\n");
		return NULL;
	}
	picture->width = width;
	picture->height = height;
	picture->pixmap = build_pixmap(picture);

	if (!(picture->pixmap)) {
		fprintf(stderr, "FF_init failed building pixmap!\n");
		return NULL;
	}
	return picture;
}


/* Serialize and write picture to stdout. return status */
int FF_write(const FarbFeld *picture) {
	/* create the binary header */
	uint8_t *header = serial_header(picture);
	if (!header) {
		fprintf(stderr, "Failed to serialize header!\n");
		return 1;
	}
	/* create the binary pixmap */
	uint8_t *pixmap = serial_pixmap(picture);
	if (!pixmap) {
		fprintf(stderr, "Failed to serialize pixmap!\n");
		return 1;
	}
	int pixmap_len = picture->width * picture->height * FF_PIXEL_SIZE;
	/* write header */
	for (int i=0; i<FF_HEADER_SIZE; i++) {
		putchar(header[i]);
	}
	/* write pixmap */
	for (int i=0; i < pixmap_len; i++) {
		putchar(pixmap[i]);
	}
	return 0; /* success */
}


Pixel** FF_plot_pos(FarbFeld *picture, Point *pos, int npos) {
	Pixel **pixmap = picture->pixmap;
	Point p;
	uint32_t row;
	uint32_t col;
	for (int i = 0; i < npos; i++) {
		p = denormalize(pos[i], picture->width-1, picture->height-1);
		row = (uint32_t) p.y;
		col = (uint32_t) p.x;
		pixmap[row][col].R += 0x1fff;
	}
	return pixmap;
}


/* 'private' functions */
/* Return a pixmap corresponding to the picture dimensions in the header */
Pixel** build_pixmap(FarbFeld *picture) {
	Pixel **pixmap = malloc(picture->height * sizeof(Pixel*));
	if (!pixmap) {
		fprintf(stderr, "Could not allocate **pixmap!\n");
		return NULL;
	}
	/* create pixmap */
	for (int row = 0; row < picture->height; row++) {
		pixmap[row] = malloc(picture->width * sizeof(Pixel));
		if (!(pixmap[row])) {
			fprintf(stderr, "Could not allocate pixmap row: %d", row);
			return NULL;
		}
	}

	/* initialize to all zeros */
	/* for each row of pixels */
	for (int row = 0; row < (picture->height); row++) {
		/* set each pixel */
		for (int col = 0; col < (picture->width); col++) {
			pixmap[row][col].R = 0;
			pixmap[row][col].G = 0;
			pixmap[row][col].B = 0;
			pixmap[row][col].A = 0xffff; 
		}
	}
	return pixmap;
}


/* Return serialized header */
uint8_t* serial_header(const FarbFeld *picture) {	
	/* build magic field */
	uint8_t smagic[8] = "farbfeld";
	uint8_t *h0 = smagic;
	/* width field */
	uint32_t BE_width = bswap_32(picture->width);
	uint8_t *h1 = (uint8_t*) &BE_width;
	/* height field */
	uint32_t BE_height = bswap_32(picture->height);
	uint8_t *h2 = (uint8_t*) &BE_height;
	/* output space */
	uint8_t *output = malloc(FF_HEADER_SIZE);
	if (!output) {
		return NULL;
	}
	/* write to output */
	memcpy(output, h0, 8);
	memcpy(output+8, h1, 4);
	memcpy(output+12, h2, 4);
	return output;
}


/* Return a serialized pixmap */
uint8_t* serial_pixmap(const FarbFeld *picture) {
	Pixel **pixmap = picture->pixmap;
	/* setup output space */
	int pixlen = picture->width * picture->height * FF_PIXEL_SIZE;
	uint8_t *output = malloc(pixlen);
	if (!output) {
		return NULL;
	}

	int out_cursor = 0;
	uint8_t *p;
	for (int row = picture->height-1; row >= 0; row--) {
		for (int col = 0; col < picture->width; col++) {
			p = serial_pixel(pixmap[row][col]);
			if (!p) {
				fprintf(stderr, "Failed to serialize pixel (%d, %d)\n", col, row);
				return NULL;
			}
			memcpy(output+out_cursor, p, FF_PIXEL_SIZE);
			out_cursor += FF_PIXEL_SIZE;
		}
	}

	return output;
}

uint8_t* serial_pixel(const Pixel p) {
	uint16_t *sp = malloc(FF_PIXEL_SIZE);
	if (!sp) {
		fprintf(stderr, "Failed to allocate memory for pixel serialization!\n");
		return NULL;
	}
	
	sp[0] = bswap_16(p.R);
	sp[1] = bswap_16(p.G);
	sp[2] = bswap_16(p.B);
	sp[3] = bswap_16(p.A);
	
	return (uint8_t*) sp;
}
