#include "objects.h"

Vect radiance(const Ray &ray, int &depth, const Univers &univers)
{
	if (depth == max_depth)
		return Vect();
	const Sphere& obstacle = ray.nearest_object();
	if (obstacle == Sphere())
		return Vect();
}