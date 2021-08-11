#include <iostream>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>


struct Vect3
{
	double x, y, z;
	double coeffs[3];

	Vect3(const double &x_ = 0, const double &y_ = 0, const double &z_ = 0)
	{
		x = x_, coeffs[0] = x;
		y = y_, coeffs[1] = y;
		z = z_, coeffs[2] = z;
	}
	Vect3(const double coeffs_[3])
	{
		x = coeffs_[0], coeffs[0] = x;
		y = coeffs_[1], coeffs[1] = y;
		z = coeffs_[2], coeffs[2] = z;
	}

	Vect3 operator+(const Vect3& v) const { return Vect3(x + v.x, y + v.y, z + v.z); }
	Vect3 operator+=(const Vect3& v) const { return *this + v; }
	Vect3 operator-(const Vect3& v) const { return Vect3(x - v.x, y - v.y, z - v.z); }
	Vect3 operator*(const double& l) const { return Vect3(l * x, l * y, l * z); }
	Vect3 operator/(const double& l) const { return (*this)*(1/l); }
	Vect3 operator*(const Vect3& v) const { return Vect3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
	bool operator==(const Vect3& v) const { return x == v.x && y == v.y && z == v.z; }

	void normalize() { *this = *this * (1 / sqrt(dot(*this))); }
	Vect3 normalized() const { Vect3 v = *this; v.normalize(); return v; }
	double dot(const Vect3& v) const { return x * v.x + y * v.y + z * v.z; }
};

Vect3 operator*(const double& l, const Vect3& v) { return v * l; }

std::ostream& operator<<(std::ostream& os, const Vect3& v)
{
	os << "(" << v.x << ", " << v.y << ", " << v.z << ")"; // Careful if you put ' instead of " it will cout an integer instead of ', '
	return os;
}

struct Matrix3 // Create a proper Matrix3 class from which Vector3 inherits
{
	double coeffs[9];

	Matrix3(const Vect3& col1, const Vect3& col2, const Vect3& col3)
	{
		for (int i = 0; i < 3; i++)
			coeffs[3 * i] = col1.coeffs[i], coeffs[3 * i + 1] = col2.coeffs[i], coeffs[3 * i + 2] = col3.coeffs[i];
	}

	Vect3 operator*(const Vect3& v) const
	{
		double coeffs_[3];
		for (int i = 0; i < 3; i++)
		{
			double coeff = 0;
			for (int j = 0; j < 3; j++)
				coeff += coeffs[3 * i + j] * v.coeffs[j];
			coeffs_[i] = coeff;
		}
		return Vect3(coeffs_);
	}
};

enum refl_type {
	DIFF,
	REFR,
	SPEC
};

struct Sphere
{
	double r;
	Vect3 c, col, e;
	refl_type tp;

	Sphere(double r_ = 0, Vect3 c_ = Vect3(), Vect3 col_ = Vect3(), Vect3 e_ = Vect3(), refl_type tp_ = DIFF)
	{
		r = r_;
		c = c_;
		col = col_;
		e = e_;
		tp = tp_;
	}

	bool operator==(const Sphere& s) const { return r == s.r && c == s.c && col == s.col && e == s.e && tp == s.tp;  }
};

struct Univers
{
	double smallest_dim;
	int nb_spheres;
	Sphere* spheres;
	// There could be other objects later on

	Univers(const double& smallest_dim_, const Sphere spheres_[])
	{
		smallest_dim = smallest_dim_;
		nb_spheres = int(sizeof(spheres_) / sizeof(Sphere));
		spheres = new Sphere[nb_spheres];
		for (int i = 0; i < nb_spheres; i++)
			spheres[i] = spheres_[i];
	}

	~Univers() { delete[] spheres; }

	int get_nb_objects() const { return nb_spheres; }
};

enum object_types {
	SPHERE,
	// more to come
};

struct Ray
{
	Vect3 o, d;
	double length;

	Ray(Vect3 o_, Vect3 d_, double length_ = 0)
	{
		o = o_, d = d_, length = length_;
		d.normalize();
	}

	const double intersect(const Sphere& s) const
	{
		double b, delta;
		b = (o - s.c).dot(d);
		delta = b * b - ((o - s.c).dot(o - s.c) - s.r * s.r);
		if (delta < 0)
			return 0;
		else
		{
			double t1 = -b - sqrt(delta), t2 = -b + sqrt(delta);
			return t2 > 0 ? (t1 > 0 ? t1 : t2) : 0;
		}
	}

	// would be prettier with an Object class and the Sphere one inheriting from it
	const Sphere nearest_object(const Univers& univers)
	{
		if (univers.get_nb_objects() == 0)
			return Sphere();
		double val = -1;
		int i_val = 0;
		object_types obj = SPHERE;
		if (univers.nb_spheres > 0)
		{
			val = intersect(univers.spheres[0]);
			for (int i = 1; i < univers.nb_spheres; i++)
			{
				double new_val = intersect(univers.spheres[i]);
				if (((univers.smallest_dim < new_val) && (new_val < val)) || ((val < univers.smallest_dim) && (univers.smallest_dim < new_val)))
				{
					val = new_val;
					i_val = i;
				}
			}
		}
		// elif (univers.nb_triangles > 0) double val2 = .. i_val2 = .. etc. if (val2 < val) val = val2 i_val = i_val2
		if (val > univers.smallest_dim)
			if (obj == SPHERE)
			{
				length = val;
				return univers.spheres[i_val];
			}
			// elif (obj == TRIANGLE)
		return Sphere();
	}
};

struct Camera
{
	Vect3 pos, dir; // dir = cx
	double incl; // angle cy does with the horizontal
	double h_FoV, v_FoV; // as in Field fo View. Based on human characteristics by default

	Camera(const Vect3& pos_ = Vect3(), const Vect3& dir_ = Vect3(1), const double& incl_ = 0, const double& h_FoV_ = 2 * M_PI / 3, const double& v_FoV_ = 2 * M_PI / 3)
	{
		pos = pos_, dir = dir_;
		dir.normalize();
		incl = incl_;
		h_FoV = h_FoV_, v_FoV = v_FoV_;
	}
};