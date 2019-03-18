#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include "geometry.h"
#include "ray.h"
#include "hitablelist.h"
#include "sphere.h"
#include "camera.h"

using namespace std;

Vec3f get_pixel(Ray ray, Hitable* world)
{
	//Check Intersections
	HitRecord rec;
	if (world->hit(ray, 0, FLT_MAX, rec))
		return Vec3f(rec.normal.x + 1, rec.normal.y + 1, rec.normal.z + 1) * 0.5;

	//Skybox
	float t = 0.5 * (ray.direction.y + 1.0);
	return Vec3f(1, 0, 1) * (1 - t) + Vec3f(0, 0, 0) * t;
}

void render()
{
	//Canvas variables
	const int width = 1024;
	const int height = 768;
	vector<Vec3f> framebuffer(width * height);

	//Camera
	const int samples = 5;
	Camera camera(Vec3f(0, 0, 0), 90, width / float(height));

	//World
	Hitable* list[2];
	list[0] = new Sphere(Vec3f(0, 0, -1), 0.5);
	list[1] = new Sphere(Vec3f(0, -100.5, -1), 100);
	Hitable* world = new HitableList(list, 2);

	//Main loop
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			Vec3f col(0, 0, 0);
			for (int k = 0; k < samples; k++)
			{
				//Invert y to make it pointing upwards
				float u = ((2 * (j + (rand()/ float(RAND_MAX))) / float(width) - 1));
				float v = -((2 * (i + (rand() / float(RAND_MAX))) / float(height) - 1));

				Ray ray = camera.get_ray(u, v);
				col = col + get_pixel(ray, world);
			}

			col = col * (1 / float(samples));
			framebuffer[i * width + j] = col;
		}

	//Creating Image
	ofstream ofs;
	ofs.open("./output.ppm");
	ofs << "P3\n" << width << " " << height << "\n255\n";
	for (int i = 0; i < width * height; i++)
	{
		for (int j = 0; j < 3; j++)
			ofs << (int)(255 * framebuffer[i][j]) << " ";
		ofs << "\n";
	}
	ofs.close();
}

int main()
{
	render();
	return 0;
}
