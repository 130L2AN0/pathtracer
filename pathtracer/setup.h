#pragma once

#include "objects.h"

enum dimensions
{
	SIDE = 100,
	RADIUS = int(1e5),
	BALL_RADIUS = 15
};

Sphere
bottom(RADIUS, Vect(SIDE / 2, SIDE / 2, -RADIUS), Vect(.25, .75, .75), Vect(), DIFF),
left(RADIUS, Vect(-RADIUS, SIDE / 2, SIDE / 2), Vect(.75, .25, .75), Vect(), DIFF),
back(RADIUS, Vect(SIDE / 2, SIDE + RADIUS, SIDE / 2), Vect(.75, .75, .25), Vect(), DIFF),
right(RADIUS, Vect(SIDE + RADIUS, SIDE / 2, SIDE / 2), Vect(.25, .25, .75), Vect(), DIFF),
front(RADIUS, Vect(SIDE / 2, -RADIUS, SIDE / 2), Vect(.25, .75, .25), Vect(), DIFF),
top(RADIUS, Vect(SIDE / 2, SIDE / 2, SIDE + RADIUS), Vect(.75, .25, .25), Vect(), DIFF),
first(BALL_RADIUS, Vect(60, 40, BALL_RADIUS), Vect(1, 1, 1), Vect(), REFR),
second(BALL_RADIUS, Vect(20, 70, BALL_RADIUS), Vect(1, 1, 1), Vect(), SPEC),
light(SIDE / 20, Vect(SIDE / 2, SIDE / 2, SIDE + 499.374608886), Vect(10), Vect(10, 10, 10), DIFF);

const Sphere BASIC_SETUP[] = { bottom, left, back, right, front, top, first, second, light };