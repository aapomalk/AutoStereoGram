
PICTURE* depthmap2stereogram(PICTURE *depthmap, int maxdepth, int mindepth, PIXEL* (*initial_pixels)(int, int));
int depth(PICTURE *depthmap, int x, int y, int maxdepth, int mindepth);
PIXEL* random(int x, int y);