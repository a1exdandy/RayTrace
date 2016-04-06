#ifndef _LIGHT_H
#define _LIGHT_H

#include "Vec3.h"

class Light {
	Vec3 point;
	double lightness;
public:
	Light(Vec3 point, double lightness);
	const Vec3 getPoint() const;
	const double getLightness() const;
};

#endif