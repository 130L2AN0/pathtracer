#ifndef _CORE_H
#define _CORE_H

#include "objects.h"



inline double random_01() { return (double)rand() / (double)RAND_MAX; }

inline double clamp(double x) {	return x < 0 ? 0 : x>1 ? 1 : x; }

inline int toInt(double x) { return int(pow(clamp(x), 1 / 2.2) * 255 + .5); } // Applies a gamma correction of 2.2. This seems important in optics



Vec3 radiance(Ray& ray, int& depth, const int& max_depth, const Univers& uni);

int output(const Univers& uni, const int& nb_samples = 1, const int& width_resol = 512, const int& max_depth = 10);

#endif