#include <stdio.h>
#include <math.h>
#include "geom.h"

Point move(Point pos, Vector v, double scale) {
	pos.x = pos.x + scale*v.vx;
	pos.y = pos.y + scale*v.vy;
	return pos;
}

Vector rotate_vector(Vector v, double deg) {
	double rads = (2*M_PI)*deg/360;
	Vector rv;
	rv.vx = v.vx * cos(rads) - v.vy * sin(rads);
	rv.vy = v.vx * sin(rads) + v.vy * cos(rads);
	return rv;
}

Vector direction(Point a, Point b) {
	Vector v;
	v.vx = b.x - a.x;
	v.vy = b.y - a.y;
	return v;
}

Point denormalize(Point p, int xsize, int ysize) {
	Point denorm_p;
	denorm_p.x = xsize * (p.x);
	denorm_p.y = ysize * (p.y);
	return denorm_p;
}


