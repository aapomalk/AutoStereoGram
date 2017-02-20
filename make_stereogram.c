#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "read_and_print_functions.h"
#include "make_stereogram.h"
#define COLORMAX 255

PICTURE* depthmap2stereogram(PICTURE *depthmap, int maxdepth, int mindepth, PIXEL* (*initial_pixels)(int, int)) {
	PICTURE *stereogram = create_picture(depthmap->x+maxdepth, depthmap->y);
	int x,y;
	
	for (y=0; y<stereogram->y; y++) {
		for (x=0; x<stereogram->x; x++) {
			if (x < maxdepth) {
				PIXEL *new = initial_pixels(x, y);
				(*(stereogram->pic+(y+1)*x))[0] = (*new)[0];
				(*(stereogram->pic+(y+1)*x))[1] = (*new)[1];
				(*(stereogram->pic+(y+1)*x))[2] = (*new)[2];
			} else {
				PIXEL *new;
				new = (stereogram->pic+(y+1)*x - depth(depthmap, x, y, maxdepth, mindepth));
				(*(stereogram->pic+(y+1)*x))[0] = (*new)[0];
				(*(stereogram->pic+(y+1)*x))[1] = (*new)[1];
				(*(stereogram->pic+(y+1)*x))[2] = (*new)[2];
			}
		}
	}
	
	return stereogram;
}

int depth(PICTURE *depthmap, int x, int y, int maxdepth, int mindepth) {
	int avg = 0;
	x -= maxdepth;
	avg += depthmap->pic[(y+1)*x][0];
	avg += depthmap->pic[(y+1)*x][1];
	avg += depthmap->pic[(y+1)*x][2];
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