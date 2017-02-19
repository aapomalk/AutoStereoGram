
void print_only_red(int x, int y, FILE *fp);
void print_copy(int x, int y, FILE *fp);
void print_from_file(int mode, int x, int y, FILE *fp);
char * set_get_filename(char *filename, int mode);
FILE * read_header_of_ppm(FILE **fp, int *x, int *y);
int set_get_x(int x, int mode);
int set_get_y(int y, int mode);

typedef uint8_t PIXEL [3];