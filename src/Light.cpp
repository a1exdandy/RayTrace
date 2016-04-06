#include "Light.h"

Light::Light(Vec3 point, double lightness)
	: point(point),
	lightness(lightness) {}


const Vec3 Light::getPoint() const {
	return point;
}

const double Light::getLightness() const {
	return lightness;
}