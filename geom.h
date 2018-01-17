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

Vector rotate_vector(Vector v, double deg); 

Vector direction(Point a, Point b);

Point denormalize(Point p, int xsize, int ysize);
