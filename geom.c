#include "geom.h"

Point move(Point pos, Vector v, double scale) {
	pos.x = pos.x + scale*v.vx;
	pos.y = pos.y + scale*v.vy;
	return pos;
}

Vector direction(Point a, Point b) {
	Vector v;
	v.vx = b.x - a.x;
	v.vy = b.y - a.y;
	return v;
}

Point denormalize(Point p, int xsize, int ysize) {
	Point dp;
	dp.x = xsize*p.x;
	dp.y = ysize*p.y;
	return dp;
}


