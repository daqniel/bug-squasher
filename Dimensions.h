#ifndef _DIMENSIONS_H
#define _DIMENSIONS_H

struct Dimensions {

	Dimensions(int x, int y) {
		width = x;
		height = y;
	}
	unsigned int width;
	unsigned int height;
};

#endif
