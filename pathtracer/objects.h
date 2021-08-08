#include <iostream>
#include <string>
#include <cmath>

struct Vect
{
	double x, y, z;

	Vect(const double &x_ = 0, const double &y_ = 0, const double &z_ = 0)
	{
		x = x_;
		y = y_;
		z = z_;
	}

	Vect operator+(const Vect& u) const { return Vect(x + u.x, y + u.y, z + u.z); }
	Vect operator-(const Vect& u) const { return Vect(x - u.x, y - u.y, z - u.z); }
	Vect operator*(const double& l) const { return Vect(l * x, l * y, l * z); }

	void normalize() { *this = *this * (1 / sqrt(this->dot(*this))); }
	double dot(const Vect& u) const { return x * u.x + y * u.y + z * u.z; }
};

enum type {
	DIFF,
	REFR,
	SPEC
};

struct Sphere
{
	double r;
	Vect c, col, e;
	type tp;

	Sphere(double r_ = 0, Vect c_ = 0, Vect col_ = 0, Vect e_ = 0, type tp_ = DIFF)
	{
		r = r_;
		c = c_;
		col = col_;
		e = e_;
		tp = tp_;
	}
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
	Vect o, d;
	double length;

	Ray(Vect o_, Vect d_, double length_ = 0)
	{
		o = o_, d = d_, length = length_;
		d.normalize();
	}

	double intersect(const Sphere& s) const
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
	Sphere nearest_object(const Univers& univers)
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