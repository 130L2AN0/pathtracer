#include <string>
#include <cmath>

struct Vect
{
	double x, y, z;

	Vect(double x_ = 0, double y_ = 0, double z_ = 0)
	{
		x = x_;
		y = y_;
		z = z_;
	}

	Vect operator+(Vect& u) const { return Vect(x + u.x, y + u.y, z + u.z); }
	Vect operator-(const Vect& u) const { return Vect(x - u.x, y - u.y, z - u.z); }
	Vect operator*(const double& l) const { return Vect(l * x, l * y, l * z); }

	void normalize() { *this = *this * (1 / (*this).dot(*this)); }
	double dot(const Vect& u) const { return x * u.x + y * u.y + z * u.z; }
};

struct Ray
{
	Vect o, d;

	Ray(Vect o_, Vect d_)
	{
		o = o_, d = d_;
		d.normalize();
	}
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

	Sphere(double r_, Vect c_, Vect col_, Vect e_, type tp_)
	{
		r = r_;
		c = c_;
		col = col_;
		e = e_;
		tp = tp_;
	}

	double intersect(const Ray &ray) const
	{
		double b, delta;
		b = (ray.o-c).dot(ray.d);
		delta = b*b - ((ray.o-c).dot(ray.o-c) - r*r);
		if (delta < 0)
			return 0;
		else
		{
			double t1 = -b - sqrt(delta), t2 = -b + sqrt(delta);
			return t2 > 0 ? (t1 > 0 ? t1 : t2) : 0;
		}
	}
};