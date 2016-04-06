#ifndef _RAYTRACE_H
#define _RAYTRACE_H

#include "Vec3.h"
#include "Light.h"
#include "Object.h"


const double ambientColorCoefficient = 0.15;
const Vec3 backgroundColor(0, 0, 0);
const double airRefractionIndex = 1.0;
const Vec3 lightColor(1, 1, 1);


const Vec3 rayTrace(const Vec3 &point, const Vec3 &direction, const std::vector<Object *> &objects, const std::vector<Light> &lights, int traceDepth = 0);
const unsigned long vectorToColor(const Vec3 &vecto);
const Vec3 reflect(const Vec3 &vector, const Vec3 &normal);

#endif