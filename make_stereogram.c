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
	
	for (y=(stereogram->y)-1; y>=0; y--) {
		for (x=(stereogram->x)-1; x>=0; x--) {
			if (x < maxdepth || 1) {
				PIXEL *new = initial_pixels(x, y);
				(*(stereogram->pic+x+y*stereogram->x))[0] = (*new)[0];
				(*(stereogram->pic+x+y*stereogram->x))[1] = (*new)[1];
				(*(stereogram->pic+x+y*stereogram->x))[2] = (*new)[2];
			} else {
				PIXEL *new;
				int dep = depth(depthmap, x, y, maxdepth, mindepth);
				new = (stereogram->pic+x+y*stereogram->x - dep);
				(*(stereogram->pic+x+y*stereogram->x))[0] = (*new)[0];
				(*(stereogram->pic+x+y*stereogram->x))[1] = (*new)[1];
				(*(stereogram->pic+x+y*stereogram->x))[2] = (*new)[2];
				if (dep != maxdepth) {
					printf("depth: %d, x: %d, y: %d\n", dep, x, y);
				}
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