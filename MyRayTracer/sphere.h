#pragma once
#include "hitable.h"

class Sphere : public Hitable
{
public:
	Vec3f center;
	float radius;

	Sphere() {}
	Sphere(Vec3f c, float r) : center(c), radius(r) {}
	virtual bool hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const;
};

bool Sphere::hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const
{
	Vec3f oc = ray.origin - center;
	float a = dot(ray.direction, ray.direction);
	float b = 2 * dot(ray.direction, oc);
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	if (discriminant > 0)
	{
		float t = (-b - sqrt(discriminant)) / (2 * a);
		if (t > tMin && t < tMax)
		{
			record.t = t;
			record.point = ray.getPoint(t);
			record.normal = (record.point - center).normalize();
			return true;
		}
		t = (-b + sqrt(discriminant)) / (2 * a);
		if (t > tMin && t < tMax)
		{
			record.t = t;
			record.point = ray.getPoint(t);
			record.normal = (record.point - center).normalize();
			return true;
		}
	}
	return false;
}