/* returns an array of positions */
Point*
chaos(unsigned int iterations, unsigned int seed);

/* private functions */
int 
move_allowed(int rule, int prev, int pf, int curr, int cf, int next, int verts);
