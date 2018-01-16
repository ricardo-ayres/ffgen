/* General geometry stuff */

typedef struct Point_s {
	double x;
	double y;
} Point;

typedef struct Vector_s {
	double vx;
	double vy;
} Vector;

Point move(Point pos, Vector v, double scale);
Vector direction(Point a, Point b);

