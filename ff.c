#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <byteswap.h>

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


/* Return a pixmap corresponding to the picture dimensions in the header */
Pixel** build_pixmap(FarbFeld *picture) {
	Pixel **pixmap = malloc(picture->height * sizeof(Pixel*));
	if (!pixmap) {
		fprintf(stderr, "Could not allocate **pixmap!\n");
		return NULL;
	}
	/* create pixmap */
	for (int i = 0; i < picture->width; i++) {
		pixmap[i] = malloc(sizeof(Pixel));
		if (!(pixmap[i])) {
			fprintf(stderr, "Could not allocate pixmap[%d]", i);
			return NULL;
		}
	}
	/* initialize to all zeros */
	for (int i = 0; i < picture->height; i++) {
		for (int j = 0; j < picture->width; j++) {
			pixmap[i][j].R = 0;
			pixmap[i][j].G = 0;
			pixmap[i][j].B = 0;
			pixmap[i][j].A = 0xffff; 
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
	/* helper variables */
	uint16_t BE_R, BE_G, BE_B, BE_A;
	uint8_t *pR, *pG, *pB, *pA;
	/* byte counter to advande output */
	int bc = 0;
	for (int i = 0; i < picture->height; i++) {
		for (int j = 0; j < picture->width; j++) {
			/* red channel */
			BE_R = bswap_16(pixmap[i][j].R);
			pR = (uint8_t*) &BE_R;
			memcpy(output+bc, pR, 2);
			bc += 2;
			/* green channel */
			BE_G = bswap_16(pixmap[i][j].G);
			pG = (uint8_t*) &BE_G;
			memcpy(output+bc, pG, 2);
			bc += 2;
			/* blue channel */
			BE_B = bswap_16(pixmap[i][j].B);
			pB = (uint8_t*) &BE_B;
			memcpy(output+bc, pB, 2);
			bc += 2;
			/* alpha channel */
			BE_A = bswap_16(pixmap[i][j].A);
			pA = (uint8_t*) &BE_A;
			memcpy(output+bc, pA, 2);
			bc += 2;
		}
	}
	return output;
}

