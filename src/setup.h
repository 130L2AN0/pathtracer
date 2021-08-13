#include "core.h"

enum dimensions
{
	SIDE = 100,
	RADIUS = int(1e5),
	BALL_RADIUS = 15
};

Sphere
BOTTOM(RADIUS, Vec3(SIDE / 2, SIDE / 2, -RADIUS), Vec3(), Vec3(.75, .75, .75), DIFF),
LEFT(RADIUS, Vec3(-RADIUS, SIDE / 2, SIDE / 2), Vec3(), Vec3(.75, .25, .25), DIFF),
BACK(RADIUS, Vec3(SIDE / 2, SIDE + RADIUS, SIDE / 2), Vec3(), Vec3(.75, .75, .75), DIFF),
RIGHT(RADIUS, Vec3(SIDE + RADIUS, SIDE / 2, SIDE / 2), Vec3(), Vec3(.25, .25, .75), DIFF),
// FRONT(RADIUS, Vec3(SIDE / 2, -RADIUS, SIDE / 2), Vec3(), Vec3(), DIFF),
TOP(RADIUS, Vec3(SIDE / 2, SIDE / 2, SIDE + RADIUS), Vec3(), Vec3(.75, .75, .75), DIFF),
FIRST(BALL_RADIUS, Vec3(70, 70, BALL_RADIUS), Vec3(), Vec3(1, 1, 1)*.999, SPEC),
SECOND(BALL_RADIUS, Vec3(20, 85, BALL_RADIUS), Vec3(.1, .1, .1), Vec3(.25, .25, .75), DIFF),
LIGHT(500, Vec3(SIDE / 2, SIDE / 2, SIDE + 499.5), Vec3(12, 12, 12), Vec3(), DIFF);

const Sphere BASIC_SETUP[] = { BOTTOM, LEFT, BACK, RIGHT, TOP, FIRST, SECOND, LIGHT };
const int NB_SPHERES = sizeof(BASIC_SETUP) / sizeof(Sphere);
const Camera CAM(Vec3(SIDE / 2, -SIDE/4, SIDE / 2), Vec3(0, 1), 0, 2 * M_PI / 3, 2 * M_PI / 3);
const Univers UNI(NB_SPHERES, BASIC_SETUP, CAM);