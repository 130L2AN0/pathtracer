#pragma once

#include "setup.h"

int main()
{
	Vect v(0, SIDE, 0);
	Vect center(SIDE / 2, SIDE / 2, SIDE / 2);
	Ray r(center, v);
	std::cout << r.d.dot(r.d) << std::endl;
	std::cin.get();
	return 0;
}