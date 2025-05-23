
#ifndef VECTOR_H
#define VECTOR_H


#include<math.h>



#include "header.h"



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

Vector subtract (Vector u, Vector v) {
	/* Returns u - v */
	return vector(u.x - v.x, u.y - v.y);
}

float length (Vector v) {
	return sqrt(v.x * v.x + v.y * v.y);
}

float distance (Vector u, Vector v) {
	return length(subtract(v, u));
}
#endif
