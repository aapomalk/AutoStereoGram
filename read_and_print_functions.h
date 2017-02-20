
typedef uint8_t PIXEL [3];

typedef struct PICTURE {
	int x;
	int y;
	PIXEL *pic;
} PICTURE;

void print_picture(PICTURE *pic, char *filename);
void print_header(FILE *fp, int x, int y);
PICTURE* read_picture(char *filename);
PICTURE* create_picture(int x, int y);
void free_picture(PICTURE *pic);
void print_pixel(PIXEL *rgb, FILE *fp);
int read_pixel(FILE *fp, PIXEL *px);
FILE * read_header_of_ppm(FILE **fp, int *x, int *y);