#include <stdio.h>

void print_ppm(char *filename, int x, int y, void (*fun)(int, int, FILE*)) {
	FILE *fp = fopen(filename, "w");
	int i,j;
	if (!fp) {
		printf("error\n");
		return;
	}
	fprintf(fp, "P6\n#printed by AutoStereoGram by aapomalk\n%d %d\n255\n", x, y);
	for (i=0; i < y; i++) {
		for (j=0; j < x; j++) {
			fun(i, j, fp);
		}
	}
	
	fclose(fp);
}