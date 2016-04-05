#ifndef _RAYTRACE_H
#define _RAYTRACE_H

#include "Vec3.h"
#include "Light.h"
#include "Object.h"

Vec3 const rayTrace(const Vec3 &point, const Vec3 &direction, const std::vector<Object *> &objects, const std::vector<Light> &lights);
unsigned long vectorToColor(const Vec3 &vec);

#endif