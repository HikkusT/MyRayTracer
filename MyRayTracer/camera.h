#pragma once

#include <cmath>
#include "ray.h"

class Camera
{
public:
	Vec3f position;
	float field_of_view;
	float aspect;

	Camera(Vec3f pos, float fov, float asp) 
		: position(pos)
		, field_of_view(fov * M_PI / 180.)
		, aspect(asp)
	{}	

	Ray get_ray(float u, float v) const
	{
		float x = u * tan(field_of_view / 2.) * aspect;
		float y = v * tan(field_of_view / 2.);

		Vec3f dir = Vec3f(x, y, -1).unit_vector();
		return Ray(position, dir);
	}
};