#ifndef _PLANE_H
#define _PLANE_H

#include "Object.h"

class Plane : public Object{
private:
	Vec3 normal, point;
public:
	Plane(const Vec3 &point, const Vec3 &normal, double shininess, double reflectivity);
	virtual const double intersection(const Vec3 &r, const Vec3 &p) const;
	virtual const Vec3 getColor(const Vec3 &r) const;
	virtual const Vec3 getNormal(const Vec3 &r) const;
};

#endif