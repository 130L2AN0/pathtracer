#include <iostream>
#include "geometry.h"

int main()
{
	Vect v(1, 2, 3);
	Ray r(v, v);
	std::cout << r.d.x << " " << v.x << "\n";
	return 0;
}