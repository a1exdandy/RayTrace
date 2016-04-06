#include "Sphere.h"
#include <cmath>
#include <algorithm>

Sphere::Sphere(const Vec3 &center, double radius, const Vec3 &color, double shininess, double reflectivity, double refractionIndex)
	: radius(radius),
	center(center),
	color(color),
	Object(shininess, reflectivity, refractionIndex) {}

double const Sphere::intersection(const Vec3 &point, const Vec3 &direction) const {
	Vec3 v = point - center;
	double a = direction.dot(direction),
		b = v.dot(direction) * 2,
		c = v.dot(v) - radius*radius,
		D = b*b - 4 * a*c;
	// TODO: double comparation
	if (D < 0) {
		return NOT_INTERSECTED;
	}
	double t1 = (-b + sqrt(D)) / (2 * a),
		t2 = (-b - sqrt(D)) / (2 * a);
	if (t1 < 0 && t2 < 0) {
		return NOT_INTERSECTED;
	}
	if (t1 >= 0 && t2 >= 0) {
		return std::min(t1, t2);
	}
	if (t1 >= 0)
		return t1;
	return t2;
}

Vec3 const Sphere::getColor(const Vec3 &point) const {
	return color;
}

Vec3 const Sphere::getNormal(const Vec3 &point) const {
	return (point - center).normalize();
}
