#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "geometry.h"
#include "ray.h"
#include "hitablelist.h"
#include "sphere.h"

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
	//Camera variables
	const int width = 1024;
	const int height = 768;
	const float fov = 90 * 3.1415 / float(180);
	vector<Vec3f> framebuffer(width * height);

	//World
	Hitable* list[2];
	list[0] = new Sphere(Vec3f(0, 0, -1), 0.5);
	list[1] = new Sphere(Vec3f(0, -100.5, -1), 100);
	Hitable* world = new HitableList(list, 2);

	//Main loop
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			//Invert y to make it pointing upwards
			float x = ((2 * (j + 0.5) / float(width) - 1)) * tan(fov/2.) * width/float(height);
			float y = - ((2 * (i + 0.5) / float(height) - 1)) * tan(fov/2.);

			//TODO: Change normalize
			Vec3f dir = Vec3f(x, y, -1).normalize();
			Ray ray(Vec3f(0, 0, 0), dir);
			framebuffer[i * width + j] = get_pixel(ray, world);
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
