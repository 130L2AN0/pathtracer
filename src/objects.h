#ifndef _OBJECTS_H
#define _OBJECTS_H

#include "dependencies.h"



// Vec3

struct Vec3
{
	double x, y, z;
	double coeffs[3];

	Vec3(const double& x_ = 0, const double& y_ = 0, const double& z_ = 0);
	Vec3(const double coeffs_[3]);

	Vec3 operator+(const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
	void operator+=(Vec3& v) { x += v.x; y += v.y; z += v.z; }
	Vec3 operator-(const Vec3& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
	Vec3 operator*(const double& l) const { return Vec3(l * x, l * y, l * z); }
	Vec3 operator/(const double& l) const { return (*this) * (1 / l); }
	Vec3 operator%(const Vec3& v) const { return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
	bool operator==(const Vec3& v) const { return x == v.x && y == v.y && z == v.z; }

	void normalize() { *this = *this * (1 / sqrt(dot(*this))); }
	Vec3 normalized() const { Vec3 v = *this; v.normalize(); return v; }
	double dot(const Vec3& v) const { return x * v.x + y * v.y + z * v.z; }
	Vec3 mult(const Vec3& v) const { return Vec3(x * v.x, y * v.y, z * v.z); }
};

std::ostream& operator<<(std::ostream& os, const Vec3& v);



// Matrix3

struct Matrix3 // Create a proper Matrix3 class from which Vector3 inherits
{
	double coeffs[9];

	Matrix3(const Vec3& col1, const Vec3& col2, const Vec3& col3);

	Vec3 operator*(const Vec3& v) const
	{
		double coeffs_[3];
		for (int i = 0; i < 3; i++)
		{
			double coeff = 0;
			for (int j = 0; j < 3; j++)
				coeff += coeffs[3 * i + j] * v.coeffs[j];
			coeffs_[i] = coeff;
		}
		return Vec3(coeffs_);
	}
};



// Sphere

enum refl_type {
	DIFF,
	SPEC,
	REFR
};

struct Sphere
{
	double r;
	Vec3 c, col, e;
	refl_type tp;

	Sphere(double r_ = 0, Vec3 c_ = Vec3(), Vec3 e_ = Vec3(), Vec3 col_ = Vec3(), refl_type tp_ = DIFF);

	bool operator==(const Sphere& s) const { return r == s.r && c == s.c && col == s.col && e == s.e && tp == s.tp;  }
};



// Camera

struct Camera
{
	Vec3 pos, dir; // dir = cx
	double incl; // angle cy does with the horizontal
	double h_FoV, v_FoV; // as in Field fo View. Based on human characteristics by default

	Camera(const Vec3& pos_ = Vec3(), const Vec3& dir_ = Vec3(1), const double& incl_ = 0, const double& h_FoV_ = 2 * M_PI / 3, const double& v_FoV_ = 2 * M_PI / 3);
};



// Univers

struct Univers
{
	double smallest_dim;
	int nb_spheres;
	Sphere* spheres;
	Camera cam;
	// There could be other objects later on

	Univers(const int& nb_spheres_, const Sphere spheres_[], const Camera cam_ = Camera(), const double& smallest_dim_ = 1e-5);

	~Univers() { delete[] spheres; }

	int get_nb_objects() const { return nb_spheres; }
};

enum object_types {
	SPHERE,
	// more to come
};



// Ray

struct Ray
{
	Vec3 o, d;
	double length;

	Ray(Vec3 o_, Vec3 d_, double length_ = 0);

	const double intersect(const Sphere& s) const;

	// would be prettier with an Object class and the Sphere one inheriting from it
	const Sphere nearest_object(const Univers& univers);
};

#endif