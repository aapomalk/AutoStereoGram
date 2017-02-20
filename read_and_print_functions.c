#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "read_and_print_functions.h"

void print_picture(PICTURE *pic, char *filename) {
	FILE *fp = fopen(filename, "w");
	int i,j;
	if (!fp) {
		printf("error\n");
		return;
	}
	print_header(fp, pic->x, pic->y);
	for (j=0; j<pic->y; j++) {
		for (i=0; i<pic->x; i++) {
			print_pixel(pic->pic+i+j*pic->x, fp);
		}
	}
	printf("printing file %s complete\n", filename);
	fclose(fp);
}

void print_header(FILE *fp, int x, int y) {
	fprintf(fp, "P6\n#printed by AutoStereoGram by aapomalk\n%d %d\n255\n", x, y);
}

PICTURE* read_picture(char *filename) {
	FILE *fp = fopen(filename, "r");
	PICTURE *pic;
	int x,y,num,i,j;
	if (!fp) {
		printf("error opening file %s\n", filename);
		return NULL;
	}
	fp = read_header_of_ppm(&fp, &x, &y);
	pic = create_picture(x, y);
	
	for (j=0; j<y; j++) {
		for (i=0; i<x; i++) {
			num = read_pixel(fp, &pic->pic[i+x*j]);
			if (num != 3) {
				printf("error reading pixel, abort\n");
				return NULL;
			}
		}
	}
	
	fclose(fp);
	printf("reading %s complete\n", filename);
	return pic;
}

PICTURE* create_picture(int x, int y) {
	PICTURE *pic = malloc(sizeof(PICTURE));
	pic->x = x;
	pic->y = y;
	pic->pic = malloc(x*y*sizeof(PIXEL));
	return pic;
}

void free_picture(PICTURE *pic) {
	free(pic->pic);
	free(pic);
}

int read_pixel(FILE *fp, PIXEL *px) {
	return fscanf(fp, "%c%c%c", &(*px)[0], &(*px)[1], &(*px)[2]);
}

void print_pixel(PIXEL *rgb, FILE *fp) {
	fprintf(fp, "%c%c%c", (*rgb)[0], (*rgb)[1], (*rgb)[2]);
}

FILE * read_header_of_ppm(FILE **fp, int *x, int *y) {
	int z = 0, d;
	size_t n = 30;
	char *line = malloc(n*sizeof(char));
	
	while (1) {
		int num = getline(&line, &n, *fp);
		if (line[0] == '#') {
			continue;
		}
		if (num == 0) {
			printf("empty line, abort\n");
			fclose(*fp);
			return NULL;
		}
		switch (z) {
			case 0: 
			if (strcmp(line, "P6\n") != 0) {
				printf("not P6 type, abort\n");
				fclose(*fp);
				return NULL;
			} else {
				z = 1;
			}
			break;
			case 1:
			z = sscanf(line, "%d %d\n", x, y);
			if (z != 2) {
				printf("dimensions failed, abort\n");
				fclose(*fp);
				return NULL;
			}
			break;
			case 2:
			z = sscanf(line, "%d\n", &d);
			if (z != 1 && d != 255) {
				printf("colorscale failed, abort\n");
				fclose(*fp);
				return NULL;
			}
			printf("reading header succesfull\n");
			return *fp;
			break;
			default:
			printf("something went wrong, abort\n");
			fclose(*fp);
			return NULL;
		}
	}
}