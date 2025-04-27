#include <math.h>

typedef struct {
	int x, y;
} Vector;

Vector vector (int x, int y) {
	Vector v;
	v.x = x;
	v.y = y;
	return v;
}

Vector add (Vector u, Vector v) {
	return vector(u.x + v.x, u.y + v.y);
}

Vector scale (Vector v, int scalar) {
	return vector(scalar * v.x, scalar * v.y);
}

Vector substract (Vector u, Vector v) {
	/* Returns u - v */
	return vector(u.x - v.x, u.y - v.y);
}

float length (Vector v) {
	return sqrt(v.x * v.x + v.y * v.y);
}

Vector DIRECTIONS[4] = {vector(1, 0), vector(0, 1), vector(-1, 0), vector(0, -1)}
