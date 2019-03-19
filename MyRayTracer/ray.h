#pragma once
#include "geometry.h"

class Ray
{
public:
	Vec3f origin;
	Vec3f direction;

	Ray() 
	{}
	Ray(const Vec3f& a, const Vec3f& b) 
		: origin(a)
		, direction(b.unit_vector()) 
	{}

	Vec3f get_point(float t) const { return origin + t * direction;  }
};