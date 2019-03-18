#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "geometry.h"
#include "ray.h"

using namespace std;

bool hitSphere(const Vec3f &center, const float &radius, const Ray &ray)
{
	Vec3f oc = center - ray.origin;
	Vec3f proj = ray.getPoint(dot(oc, ray.direction));
	return (proj - center).length() <= radius * radius;
}

Vec3f getColor(Ray ray)
{
	if (hitSphere(Vec3f(0, 0, -1), 0.5, ray))
		return Vec3f(0, 1, 0);
	float t = 0.5 * (ray.direction.y + 1.0);
	return Vec3f(1, 0, 1) * (1 - t) + Vec3f(0, 0, 0) * t;
}

void render()
{
	const int width = 1024;
	const int height = 768;
	const float fov = 90 * 3.1415 / float(180);
	vector<Vec3f> framebuffer(width * height);

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			float x = ((2 * (j + 0.5) / float(width) - 1)) * tan(fov/2.) * width/float(height);
			float y = ((2 * (i + 0.5) / float(height) - 1)) * tan(fov/2.);
			Vec3f dir = Vec3f(x, y, -1).normalize();
			Ray ray(Vec3f(0, 0, 0), dir);
			framebuffer[i * width + j] = getColor(ray);
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
