#pragma once
#include "geometry.h"

class Ray
{
public:
	Vec3f origin;
	Vec3f direction;
	Ray() {}
	Ray(const Vec3f &a, const Vec3f &b) : origin(a), direction(b) {}
	Vec3f getPoint(float t) const { return origin + direction * t;  }
};