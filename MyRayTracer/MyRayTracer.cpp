#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "geometry.h"

using namespace std;

void render()
{
	const int width = 1024;
	const int height = 768;
	vector<Vec3f> framebuffer(width * height);

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			framebuffer[i * width + j] = Vec3f(i / float(height), 0, j / float(width));

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
