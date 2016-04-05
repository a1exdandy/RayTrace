#ifndef _SPHERE_H
#define _SPHERE_H

#include "Object.h"

class Sphere : public Object {
private:
	double radius;
	Vec3 center, color;
public:
	Sphere(const Vec3 &center, double radius, const Vec3 &color, double shininess, double reflectivity, double refractionIndex);
	virtual const double intersection(const Vec3 &point, const Vec3 &direction) const;
	virtual const Vec3 getColor(const Vec3 &point) const;
	virtual const Vec3 getNormal(const Vec3 &point) const;
};

#endif