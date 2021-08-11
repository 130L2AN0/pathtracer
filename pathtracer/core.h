#include "objects.h"

Vect3 radiance(Ray &ray, int &depth, const int &max_depth, const Univers &univers)
{
	if (depth == max_depth)
		return Vect3();
	const Sphere& obstacle = ray.nearest_object(univers);
	if (obstacle == Sphere())
		return Vect3();
}

inline double clamp(double x)
{
	return x < 0 ? 0 : x>1 ? 1 : x;
}

inline int toInt(double x) // Applies a gamma correction of 2.2. This seems important in optics
{
	return int(pow(clamp(x), 1 / 2.2) * 255 + .5);
}

int output(const int &width_resol = 512, const Camera &camera = Camera())
{
	const int depth_resol = int(width_resol / (2 * sin(camera.h_FoV / 2)));
	const int height_resol = int(2 * depth_resol * sin(camera.v_FoV / 2));
	Vect3 *image = new Vect3[width_resol * height_resol];
	const double& alpha = camera.incl;
	const Vect3& cx = camera.dir,
		cy2 = (-cx.dot(Vect3(0, 1)) * Vect3(1) + cx.dot(Vect3(1)) * Vect3(0, 1)).normalized(), // Still don't know if I should put a &
		cz2 = cx * cy2,
		cy = cos(alpha) * cy2 + sin(alpha) * cz2,
		cz = -sin(alpha) * cy2 + cos(alpha) * cz2;
	std::cout << cx << " " << cy << " " << cz << std::endl;
	for (int i = 0; i < height_resol; i++)
	{
		for (int j = 0; j < width_resol; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				// Consider making a tent filter or a certain number of samples
				double dy = width_resol / 2 - j - .5*(k%2), dz = height_resol / 2 - i - .5*(k>1);
				Matrix3 P(cx, cy, cz);
				Ray ray(camera.pos, P*Vect3(depth_resol, dy, dz));
				std::cout << Vect3(i, j, k) << " : " << ray.d << std::endl;
				Vect3 color = radiance();
				image[i * height_resol + j] += Vect3(clamp(color.x), clamp(color.y), clamp(color.z)) / 4; // /4 because there are 4 subpixels
			}
		}
	}
	FILE* f = fopen("image.ppm", "w");
	fprintf(f, "P3\n%d %d\n%d\n", width_resol, height_resol, 255);
	for (int i = 0; i < width_resol * height_resol; i++)
	{
		fprintf(f, "%d %d %d ", toInt(image[i].x), toInt(image[i].y), toInt(image[i].z));
	}
	return 0;
}