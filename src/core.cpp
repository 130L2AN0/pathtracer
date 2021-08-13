#include "core.h"

Vec3 radiance(Ray& ray, int& depth, const int& max_depth, const Univers& uni)
{
	if (depth == max_depth)
	{
		// std::cout << 0 << std::endl;
		return Vec3();
	}
	const Sphere& obstacle = ray.nearest_object(uni);
	if (obstacle == Sphere())
	{
		// std::cout << 1 << std::endl;
		return Vec3();
	}
	depth++;
	Vec3 impact = ray.o + ray.d * ray.length;
	Vec3 normal = (impact - obstacle.c).normalized();
	if (ray.d.dot(normal) > 0)
		normal = normal * -1;
	if (obstacle.tp == SPEC)
	{
		// std::cout << 2 << std::endl;
		Ray refl(impact, ray.d - normal * ray.d.dot(normal) * 2);
		return obstacle.e + obstacle.col.mult(radiance(refl, depth, max_depth, uni));
	}
	else if (obstacle.tp == DIFF)
	{
		Vec3 u = fabs(normal.dot(Vec3(1))) > .1 ? normal % Vec3(1) : normal % Vec3(0, 1); u.normalize();
		Vec3 v = normal % u;
		double phi = random_01() * 2 * M_PI, sin2theta = random_01();
		// normally for perfect randomness we would pick a theta between 0 and pi/2 and then compute its sin
		// but there we want a glossy reflection of the light, so with more chance to be refelcted up
		Vec3 new_dir = u * sqrt(sin2theta) * cos(phi) + v * sqrt(sin2theta) * sin(phi) + normal * sqrt(1 - sin2theta);
		Ray refl(impact, new_dir);
		return obstacle.e + obstacle.col.mult(radiance(refl, depth, max_depth, uni));
	}
	else
		return Vec3();
}

int output(const Univers& uni, const int& nb_samples, const int& width_resol, const int& max_depth)
{
	srand(time(NULL));
	const int depth_resol = int(width_resol / (2 * sin(uni.cam.h_FoV / 2)));
	const int height_resol = int(2 * depth_resol * sin(uni.cam.v_FoV / 2));
	Vec3* image = new Vec3[width_resol * height_resol];
	const double& alpha = uni.cam.incl;
	const Vec3& cx = uni.cam.dir,
		cy2 = (Vec3(1) * -cx.dot(Vec3(0, 1)) + Vec3(1) * cx.dot(Vec3(1)) ).normalized(), // Still don't know if I should put a &
		cz2 = cx % cy2,
		cy = cy2 * cos(alpha) + cz2 * sin(alpha),
		cz = cy2 * -sin(alpha) + cz2 * cos(alpha);
	for (int i = 0; i < height_resol; i++)
	{
		for (int j = 0; j < width_resol; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				if (i%100 == 0 && j%100 == 0)
					std::cout << "Evrthg fine thx : " << Vec3(i, j, k) << std::endl;
				for (int l = 0; l < nb_samples; l++)
				{
					// Consider making a tent filter
					double dy = width_resol / 2 - j - .5 * (k % 2), dz = height_resol / 2 - i - .5 * (k > 1);
					Matrix3 P(cx, cy, cz);
					Ray ray(uni.cam.pos, P * Vec3(depth_resol, dy, dz));
					int depth = 0;
					Vec3 color = radiance(ray, depth, max_depth, uni);
					image[i * width_resol + j] += color / (4 * nb_samples); // /4 because there are 4 subpixels
				}
			}
		}
	}
	FILE* f = fopen("image.ppm", "w");
	fprintf(f, "P3\n%d %d\n%d\n", width_resol, height_resol, 255);
	for (int i = 0; i < width_resol * height_resol; i++)
		fprintf(f, "%d %d %d ", toInt(image[i].x), toInt(image[i].y), toInt(image[i].z));
	return 0;
}