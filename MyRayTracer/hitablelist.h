#pragma once
#include "hitable.h"

class HitableList : public Hitable
{
public:
	Hitable **list;
	int listSize;

	HitableList() {}
	HitableList(Hitable **l, int n) : list(l), listSize(n) {}

	virtual bool hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const;
};

bool HitableList::hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const
{
	HitRecord temp_rec;
	bool hitAnything = false;
	double closestSoFar = tMax;
	for (int i = 0; i < listSize; i++)
	{
		if (list[i]->hit(ray, tMin, closestSoFar, temp_rec))
		{
			hitAnything = true;
			closestSoFar = temp_rec.t;
			record = temp_rec;
		}
	}
	return hitAnything;
}