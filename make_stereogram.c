#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "read_and_print_functions.h"
#include "make_stereogram.h"
#define COLORMAX 255

PICTURE* depthmap2stereogram(PICTURE *depthmap, int maxdepth, int mindepth, PIXEL* (*initial_pixels)(int, int)) {
	PICTURE *stereogram = create_picture(depthmap->x+maxdepth, depthmap->y);
	int x,y;
	printf("%d %d\n", stereogram->x, stereogram->y);
	
	for (y=0; y<(stereogram->y); y++) {
		for (x=0; x<(stereogram->x); x++) {
			if (x < maxdepth) {
				PIXEL *new;
				new = initial_pixels(x, y);
				(*(stereogram->pic+x+y*stereogram->x))[0] = (*new)[0];
				(*(stereogram->pic+x+y*stereogram->x))[1] = (*new)[1];
				(*(stereogram->pic+x+y*stereogram->x))[2] = (*new)[2];
			} else {
				PIXEL *new;
				int dep = depth(depthmap, x, y, maxdepth, mindepth);
				new = (stereogram->pic + x + y * stereogram->x - dep);
				(*(stereogram->pic+x+y*stereogram->x))[0] = (*new)[0];
				(*(stereogram->pic+x+y*stereogram->x))[1] = (*new)[1];
				(*(stereogram->pic+x+y*stereogram->x))[2] = (*new)[2];
			}
		}
	}
	
	return stereogram;
}

int depth(PICTURE *depthmap, int x, int y, int maxdepth, int mindepth) {
	int avg = 0;
	x -= maxdepth;
	avg += depthmap->pic[x+y*depthmap->x][0];
	avg += depthmap->pic[x+y*depthmap->x][1];
	avg += depthmap->pic[x+y*depthmap->x][2];
	avg /= 3;
	return maxdepth - (maxdepth - mindepth) * avg / COLORMAX;
}

PIXEL* random(int x, int y) {
	PIXEL *new = malloc(sizeof(PIXEL));
	static int first = 1;
	time_t t;
	uint8_t value;
	if (first) {
		first = 0;
		srand((unsigned) time(&t));
	}
	value = rand() % COLORMAX;
	(*new)[0] = value;
	(*new)[1] = value;
	(*new)[2] = value;
	return new;
}

PIXEL* random_color(int x, int y) {
	PIXEL *new = malloc(sizeof(PIXEL));
	static int first = 1;
	time_t t;
	if (first) {
		first = 0;
		srand((unsigned) time(&t));
	}
	(*new)[0] = rand() % COLORMAX;
	(*new)[1] = rand() % COLORMAX;
	(*new)[2] = rand() % COLORMAX;
	return new;
}

PIXEL* random_scale(int x, int y) {
	PIXEL *new = malloc(sizeof(PIXEL));
	static int first = 1;
	time_t t;
	if (first) {
		first = 0;
		srand((unsigned) time(&t));
	}
	(*new)[0] = colorscale(1, 0, 0, 1);
	(*new)[1] = colorscale(1, 1, 0, 1);
	(*new)[2] = colorscale(1, 2, 0, 1);
	return new;
}

int colorscale(int mode, int color, int min, int max) {
	static int red_min = 0, green_min = 0, blue_min = 0;
	static int red_max = 255, green_max = 255, blue_max = 255;
	static int first = 1;
	time_t t;
	
	if (first) {
		first = 0;
		srand((unsigned) time(&t));
	}
	
	if (mode == 0) {
		if (min < 0 || min > 255 || max < min || max > 255) {
			printf("limits were wrong, try again\n");
			return 0;
		}
		switch (color) {
			case 0: red_min = min; red_max = max; printf("setting red limits to %d %d\n", min, max); break;
			case 1: green_min = min; green_max = max; printf("setting green limits to %d %d\n", min, max); break;
			case 2: blue_min = min; blue_max = max; printf("setting blue limits to %d %d\n", min, max); break;
		}
	} else if (mode == 1) {
		switch (color) {
			case 0: return rand() % (red_max - red_min) + red_min;
			case 1: return rand() % (green_max - green_min) + green_min;
			case 2: return rand() % (blue_max - blue_min) + blue_min;
		}
	}
	return 0;
}

PIXEL* prepare_picture(int mode, char *filename, int x, int y) {
	static PICTURE *pic = NULL;
	if (mode == 0) {
		pic = read_picture(filename);
		return NULL;
	} else if (mode == 1) {
		return (pic->pic + (x % pic->x) + (y % pic->y) * pic->x);
	} else {
		free_picture(pic);
		return NULL;
	}
}

PIXEL* return_prepared_picture(int x, int y) {
	return prepare_picture(1, NULL, x, y);
}