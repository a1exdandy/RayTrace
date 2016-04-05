#ifndef _OBJECT_H
#define _OBJECT_H

#include "Vec3.h"

const double NOT_INTERSECTED = 1e9;
const double NOT_SHINY = -1;
const double NOT_REFLECTIVE = -1;
const double NOT_REFRACTIVE = -1;

class Object {
private:
	const double shininess;
	const double reflectivity;
	const double refractionIndex;
public:
	Object(double shininess, double reflectivity, double refractionIndex);
	virtual const double intersection(const Vec3 &point, const Vec3 &direction) const = 0;
	virtual const Vec3 getColor(const Vec3 &point) const = 0;
	virtual const Vec3 getNormal(const Vec3 &point) const = 0;
	const double getShininess() const;
	const double getReflectivity() const;
	const double getRefractionIndex() const;
};

#endif