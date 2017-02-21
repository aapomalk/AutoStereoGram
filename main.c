#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include "read_and_print_functions.h"
#include "make_stereogram.h"

void main1(int argc, char *argv[]);

int main(int argc, char *argv[]) {
	main1(argc, argv);
	return 0;
}

void main1(int argc, char *argv[]) {
	PIXEL* (*fun)(int, int) = NULL;
	char *filename1;
	char *filename2;
	int maxdepth; int mindepth;
	int used_method_ppm = 0;
	PICTURE *pic;
	PICTURE *pic2;
	if (argc > 6 || argc < 5) {
		printf("!!!--- Usage: ---!!!\n\n%s source.ppm target.ppm maxdepth mindepth method.ppm\n\n", argv[0]);
		printf("method.ppm can be omitted - and then grayscale random stereogram is used.\n");
		printf("When using method.ppm you should choose the maxdepth as the same as method.ppm width\n\n");
		printf("By setting method.ppm as flag:\n-color_random\na color random stereogram is used.\n");
		printf("There is also flag: -scale_rmin_rmax_gmin_gmax_bmin_bmax that sets the random scale");
		return;
	}
	if (argc == 5) {
		fun = random;
	} else if (strncmp(*(argv+5), "-scale_", 6) == 0) {
		int rmin, rmax, gmin, gmax, bmin, bmax;
		if (sscanf(*(argv+5), "-scale_%d_%d_%d_%d_%d_%d", &rmin, &rmax, &gmin, &gmax, &bmin, &bmax) != 6) {
			printf("wrong syntax in -scale_\n");
			printf("should be: -scale_redmin_redmax_greenmin_greenmax_bluemin_bluemax where all min and max are integers\n");
			return;
		}
		colorscale(0, 0, rmin, rmax);
		colorscale(0, 1, gmin, gmax);
		colorscale(0, 2, bmin, bmax);
		fun = random_scale;
	} else if (strcmp(*(argv+5), "-color_random") == 0) {
			fun = random_color;
	} else {
		prepare_picture(0, *(argv+5), 0, 0);
		fun = return_prepared_picture;
		used_method_ppm = 1;
	} 
	
	filename1 = *(argv+1);
	filename2 = *(argv+2);
	if (sscanf(*(argv+3), "%d", &maxdepth) != 1) {
		printf("use integers as maxdepth!\n");
		return;
	}
	if (sscanf(*(argv+4), "%d", &mindepth) != 1) {
		printf("use integers as mindepth!\n");
		return;
	}
	
	
	pic = read_picture(filename1);
	if (pic == NULL) {
		return;
	}
	pic2 = depthmap2stereogram(pic, maxdepth, mindepth, fun);
	
	print_picture(pic2, filename2);
	free_picture(pic);
	free_picture(pic2);
	if (used_method_ppm) {
		prepare_picture(-1, *(argv+5), 0, 0);
	}
}