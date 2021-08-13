#include "objects.h"



// Vec3

Vec3::Vec3(const double& x_, const double& y_, const double& z_)
{
	x = x_, coeffs[0] = x;
	y = y_, coeffs[1] = y;
	z = z_, coeffs[2] = z;
}

Vec3::Vec3(const double coeffs_[3])
{
	x = coeffs_[0], coeffs[0] = x;
	y = coeffs_[1], coeffs[1] = y;
	z = coeffs_[2], coeffs[2] = z;
}

std::ostream& operator<<(std::ostream& os, const Vec3& v)
{
	os << "(" << v.x << ", " << v.y << ", " << v.z << ")"; // Careful if you put ' instead of " it will cout an integer instead of ', '
	return os;
}



// Matrix3

Matrix3::Matrix3(const Vec3& col1, const Vec3& col2, const Vec3& col3)
{
	for (int i = 0; i < 3; i++)
		coeffs[3 * i] = col1.coeffs[i], coeffs[3 * i + 1] = col2.coeffs[i], coeffs[3 * i + 2] = col3.coeffs[i];
}



// Sphere

Sphere::Sphere(double r_, Vec3 c_, Vec3 e_, Vec3 col_, refl_type tp_)
{
	r = r_;
	c = c_;
	col = col_;
	e = e_;
	tp = tp_;
}



// Camera

Camera::Camera(const Vec3& pos_, const Vec3& dir_, const double& incl_, const double& h_FoV_, const double& v_FoV_)
{
	pos = pos_, dir = dir_;
	dir.normalize();
	incl = incl_;
	h_FoV = h_FoV_, v_FoV = v_FoV_;
}



// Univers

Univers::Univers(const int& nb_spheres_, const Sphere spheres_[], const Camera cam_, const double& smallest_dim_)
{
	smallest_dim = smallest_dim_;
	nb_spheres = nb_spheres_;
	spheres = new Sphere[nb_spheres];
	for (int i = 0; i < nb_spheres; i++)
		spheres[i] = spheres_[i];
	cam = cam_;
}



// Ray

Ray::Ray(Vec3 o_, Vec3 d_, double length_)
{
	o = o_, d = d_, length = length_;
	d.normalize();
}

const double Ray::intersect(const Sphere& s) const
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

const Sphere Ray::nearest_object(const Univers& univers)
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