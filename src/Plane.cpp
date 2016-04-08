#include "Plane.h"
#include <cmath>

Plane::Plane(const Vec3 &point, const Vec3 &normal, double shininess, double reflectivity)
	: point(point),
	normal(normal), 
	Object(shininess, reflectivity, NOT_REFRACTIVE) {}


Vec3 const Plane::getColor(const Vec3 &point) const {
	const double step = 0.1;
	Vec3 s1(-normal.y, -normal.z, normal.x),
		s2(normal.y * s1.z + normal.z * s1.y,
			normal.x*s1.z - normal.z*s1.x,
			-normal.y*s1.x - normal.x*s1.y),
		r = point - this->point;
	double dist = r.abs(),
		t1 = r.dot(s1),
		t2 = r.dot(s2);
	if ((((int)t1 + (t1 < 0 ? 1 : 0)) & 1) == (((int)t2 + (t2 < 0 ? 1 : 0)) & 1)) {
		return Vec3(0, 0, 0);
	} else {
		return Vec3(1, 1, 1);
	}
}

Vec3 const Plane::getNormal(const Vec3 &point) const {
	return normal;
}

double const Plane::intersection(const Vec3 &point, const Vec3 &direction) const {
	Vec3 v = point - this->point;
	double numerator =
		-(normal.x * v.x + normal.y * v.y + normal.z * v.z);
	double denominator = normal.x * direction.x + 
		normal.y * direction.y + normal.z * direction.z;
	// TODO: add double comparator
	if (denominator < -1e-8) {
		return numerator / denominator;
	}
	return NOT_INTERSECTED;
}