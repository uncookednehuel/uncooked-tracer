#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
public:
	sphere(point3 _center, double _radius) : center(_center), radius(_radius) {}

	bool hit(const ray& r, double rayTMin, double rayTMax, hitRecord& rec) const override {
		vec3 oc = r.origin() - center;
		auto a = r.direction().lengthSquared();
		auto halfB = dot(oc, r.direction());
		auto c = oc.lengthSquared() - radius * radius;

		auto discriminant = halfB * halfB - a * c;

		if (discriminant < 0) return false;
		auto sqrtd = sqrt(discriminant);

		//Find nearest root
		auto root = (-halfB - sqrtd) / a;
		if (root <= rayTMin || rayTMax <= root) {
			root = (-halfB + sqrtd) / a;
			if (root <= rayTMin || rayTMax <= root)
				return false;
		}

		rec.t = root;
		rec.p - r.at(rec.t);
		vec3 outwardNormal = (rec.p - center) / radius;
		rec.setFaceNormal(r, outwardNormal);

		return true;
	}

private:
	point3 center;
	double radius;
};

#endif