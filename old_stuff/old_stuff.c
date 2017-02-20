void print_only_red(int x, int y, FILE *fp);
void print_copy(int x, int y, FILE *fp);
void print_from_file(int mode, int x, int y, FILE *fp);
char * set_get_filename(char *filename, int mode);

int set_get_x(int x, int mode);
int set_get_y(int y, int mode);

void main1() {
	char *filename1 = "different_colors.ppm";
	char *filename2 = "copy_from_file.ppm";
	int x,y;
	set_get_filename(filename1, 0);
	print_from_file(0, 0, 0, NULL);
	x = set_get_x(0, 1);
	y = set_get_y(0, 1);
	print_ppm(filename2, x, y, print_copy);
}

int set_get_x(int x, int mode) {
	static int xs = 0;
	if (mode == 0) {
		xs = x;
	}
	return xs;
}

int set_get_y(int y, int mode) {
	static int ys = 0;
	if (mode == 0) {
		ys = y;
	}
	return ys;
}

char * set_get_filename(char *filename, int mode) {
	static char *static_filename = NULL;
	if (mode == 0) {
		static_filename = filename;
	}
	return static_filename;
}

void print_from_file(int mode, int x, int y, FILE *fp) {
	static FILE *copy_from_file = NULL;
	int xs, ys;
	char *filename = NULL;
	int test;
	uint8_t temp;
	PIXEL  *rgb;
	rgb = malloc(sizeof(PIXEL));
	
	switch (mode) {
		case 0: /* prepare file */
		filename = set_get_filename(filename, 1); /* 1 = get filename */
		copy_from_file = fopen(filename, "r");
		copy_from_file = read_header_of_ppm(&copy_from_file, &xs, &ys);
		set_get_x(xs, 0);
		set_get_y(ys, 0);
		printf("copy file prepared, x: %d, y: %d\n", xs, ys);
		break;
		case 1: /* copy the pixels */
		test = read_pixel(copy_from_file, rgb);/*fscanf(copy_from_file, "%c%c%c", rgb, (rgb+1), (rgb+2));*/
		if (test != 3) {
			printf("pixel copying went wrong, abort, x: %d, y: %d, rgb:\n", x, y);
			print_pixel(rgb, stdout);
			printf("\n");
			fclose(fp);
			fp = NULL;
			fclose(copy_from_file);
			free(rgb);
			return;
		}
		temp = (*rgb)[0];
		(*rgb)[0] = (*rgb)[2]; 
		(*rgb)[2] = (*rgb)[1];
		(*rgb)[1] = temp; /* changing the colors */
		print_pixel(rgb, fp);
		if (x == set_get_x(0, 1) - 1 && y == set_get_y(0, 1) - 1) {
			printf("copying finished\n");
			fclose(copy_from_file);
		}
		break;
	}
	free(rgb);
}

void print_only_red(int x, int y, FILE *fp) {
	uint8_t r = 255;
	uint8_t bg = 0;
	fprintf(fp, "%c%c%c", r, bg, bg);
}

void print_copy(int x, int y, FILE *fp) {
	print_from_file(1, x, y, fp);
}