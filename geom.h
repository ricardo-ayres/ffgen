/* General geometry stuff */

typedef struct Point_s {
	double x;
	double y;
} Point;

typedef struct Vector_s {
	double vx;
	double vy;
} Vector;

point move(point pos, vector v, double scale);
vector direction(point a, point b);

