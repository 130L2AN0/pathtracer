#pragma once

#include "core.h"

enum dimensions
{
	SIDE = 100,
	RADIUS = int(1e5),
	BALL_RADIUS = 15
};

Sphere
bottom(RADIUS, Vect3(SIDE / 2, SIDE / 2, -RADIUS), Vect3(.25, .75, .75), Vect3(), DIFF),
left(RADIUS, Vect3(-RADIUS, SIDE / 2, SIDE / 2), Vect3(.75, .25, .75), Vect3(), DIFF),
back(RADIUS, Vect3(SIDE / 2, SIDE + RADIUS, SIDE / 2), Vect3(.75, .75, .25), Vect3(), DIFF),
right(RADIUS, Vect3(SIDE + RADIUS, SIDE / 2, SIDE / 2), Vect3(.25, .25, .75), Vect3(), DIFF),
front(RADIUS, Vect3(SIDE / 2, -RADIUS, SIDE / 2), Vect3(.25, .75, .25), Vect3(), DIFF),
top(RADIUS, Vect3(SIDE / 2, SIDE / 2, SIDE + RADIUS), Vect3(.75, .25, .25), Vect3(), DIFF),
first(BALL_RADIUS, Vect3(60, 40, BALL_RADIUS), Vect3(1, 1, 1), Vect3(), REFR),
second(BALL_RADIUS, Vect3(20, 70, BALL_RADIUS), Vect3(1, 1, 1), Vect3(), SPEC),
light(SIDE / 20, Vect3(SIDE / 2, SIDE / 2, SIDE + 499.374608886), Vect3(10), Vect3(10, 10, 10), DIFF);

const Sphere BASIC_SETUP[] = { bottom, left, back, right, front, top, first, second, light };

const Camera cam(Vect3(SIDE / 2, 0, SIDE / 2), Vect3(0, 1), 0, 2 * M_PI / 3, 2 * M_PI / 3);