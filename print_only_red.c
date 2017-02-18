#include <stdio.h>
#include <inttypes.h>

void print_only_red(int x, int y, FILE *fp) {
	uint8_t r = 255;
	uint8_t bg = 0;
	fprintf(fp, "%c%c%c", r, bg, bg);
}