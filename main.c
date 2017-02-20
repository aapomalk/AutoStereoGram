#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>
#include "read_and_print_functions.h"
#include "make_stereogram.h"

void main1();

int main(int argc, char *argv[]) {
	main1();
	return 0;
}

void main1() {
	char *filename1 = "turtle.ppm";
	char *filename2 = "turtle_stereogram.ppm";
	PICTURE *pic = read_picture(filename1);
	PICTURE *pic2;
	if (pic == NULL) {
		return;
	}
	pic2 = depthmap2stereogram(pic, 200, 100, random);
	free_picture(pic);
	print_picture(pic, filename2);
	free_picture(pic2);
}