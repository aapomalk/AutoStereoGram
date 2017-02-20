#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>
#include "read_and_print_functions.h"

void main1();

int main(int argc, char *argv[]) {
	main1();
	return 0;
}

void main1() {
	char *filename1 = "different_colors.ppm";
	char *filename2 = "copy_from_file2.ppm";
	PICTURE *pic = read_picture(filename1);
	if (pic == NULL) {
		return;
	}
	print_picture(pic, filename2);
	free_picture(pic);
}