#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>
#include "print_ppm.h"
#include "print_functions.h"

int main(int argc, char *argv[]) {
	char *filename1 = "different_colors.ppm";
	char *filename2 = "copy_from_file.ppm";
	int x,y;
	set_get_filename(filename1, 0);
	print_from_file(0, 0, 0, NULL);
	x = set_get_x(0, 1);
	y = set_get_y(0, 1);
	print_ppm(filename2, x, y, print_copy);
	return 0;
}