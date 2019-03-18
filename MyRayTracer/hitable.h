#pragma once
#include "ray.h"

struct HitRecord
{
	float distance;
	Vec3f point;
	Vec3f normal;
};

class Hitable
{
public:
	virtual bool hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const = 0;
};