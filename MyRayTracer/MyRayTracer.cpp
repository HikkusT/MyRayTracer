#include "pch.h"
#include <iostream>
#include <fstream>

using namespace std;

void render()
{
	const int width = 1024;
	const int height = 768;


	//Creating Image
	ofstream ofs;
	ofs.open("./output.ppm");
	ofs << "P6\n" << width << ' ' << height << "\n255\n";
	for (int size = 0; size < width * height; size++)
		for (int i = 0; i < 3; i++)
			ofs << (char)(0);
	ofs.close();
}

int main()
{
	render();
	return 0;
}
