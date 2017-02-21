
PICTURE* depthmap2stereogram(PICTURE *depthmap, int maxdepth, int mindepth, PIXEL* (*initial_pixels)(int, int));
int depth(PICTURE *depthmap, int x, int y, int maxdepth, int mindepth);
PIXEL* random(int x, int y);
PIXEL* prepare_picture(int mode, char *filename, int x, int y);
PIXEL* return_prepared_picture(int x, int y);
PIXEL* random_color(int x, int y);
PIXEL* random_scale(int x, int y);
int colorscale(int mode, int color, int min, int max);