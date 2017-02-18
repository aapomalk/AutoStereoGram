#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>
#include "print_ppm.h"
#include "print_only_red.h"

int main(int argc, char *argv[]) {
	char *filename = "testing_red.ppm";
	int x = 20;
	int y = 17;
	print_ppm(filename, x, y, print_only_red);
	return 0;
}