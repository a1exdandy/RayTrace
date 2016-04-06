#ifndef _RAYTRACE_H
#define _RAYTRACE_H

#include "Vec3.h"
#include "Light.h"
#include "Object.h"


const double ambientColorCoefficient = 0.15;
const double distLimit = 1e-6;
const Vec3 backgroundColor(1, 1, 1);


const Vec3 rayTrace(const Vec3 &point, const Vec3 &direction, const std::vector<Object *> &objects, const std::vector<Light> &lights, int traceDepth = 0);
const unsigned long vectorToColor(const Vec3 &vecto);
const Vec3 reflect(const Vec3 &vector, const Vec3 &normal);
const Vec3 refract(const Vec3 &vector, const Vec3 &normal, double n1, double n2);

#endif