#include <vector>
#include <algorithm>
#include "Vec3.h"
#include "Object.h"
#include "Light.h"
#include "RayTracer.h"

const Vec3 rayTrace(const Vec3 &point, const Vec3 &direction, const std::vector<Object *> &objects, const std::vector<Light> &lights, int traceDepth) {
	// find nearest intersection
	Object *object = NULL;
	double min_dist = NOT_INTERSECTED;
	for (Object *obj : objects) {
		double dist = obj->intersection(point, direction);
		if (distLimit < dist && dist < min_dist) {
			object = obj;
			min_dist = dist;
		}
	}

	// not intersection found
	if (object == NULL)
		return backgroundColor;

	// intersection point
	Vec3 hit = point + (direction * min_dist);
	// normal to object in intersection point
	Vec3 nhit = object->getNormal(hit);
	//hit += nhit * 1e-9;

	Vec3 surfaceColor = object->getColor(hit);
	Vec3 ambientColor = surfaceColor * ambientColorCoefficient;
	Vec3 diffuseColor;
	Vec3 specularColor;
	Vec3 reflectedColor;
	Vec3 refractedColor;

	// calculate diffuse and specular color (Phong reflection model)
	for (const Light &lightObj : lights) {
		Vec3 lightRay = (lightObj.getPoint() - hit).normalize();
		bool inShadow = false;
		for (Object *obj : objects) {
			if (obj == object)
				continue;
			if (obj->intersection(hit, lightRay) != NOT_INTERSECTED) {
				inShadow = true;
				break;
			}
		}
		if (!inShadow) {
			if (object->getShininess() != NOT_SHINY) {
				Vec3 lightRayReflected = reflect(lightRay, nhit).normalize();
				double shininessCoefficient = lightRayReflected.dot(direction.normalize() * -1);
				if (shininessCoefficient > 0) {
					specularColor += Vec3(1, 1, 1) * pow(shininessCoefficient, object->getShininess()) * lightObj.getLightness();
				}
			}
			double diffuseCoefficient = lightRay.dot(nhit);
			if (diffuseCoefficient > 0)
				diffuseColor += surfaceColor * diffuseCoefficient * lightObj.getLightness();
		}
	}

	// calculate reflection and refraction color (Fresnel)
	// TODO

	double reflectionCoefficient = 0,
		refractionCoefficient = 0,
		airRefractionCoefficient;
	if (object->getReflectivity() != NOT_REFLECTIVE) {
		reflectionCoefficient = object->getReflectivity();
	}


	return ambientColor + diffuseColor + specularColor + reflectedColor + refractedColor;
}

const Vec3 reflect(const Vec3 &vector, const Vec3 &normal) {
	return normal * vector.dot(normal) * 2.0 - vector;
}

const Vec3 refract(const Vec3 &vector, const Vec3 &normal, double n1, double n2) {
	double n = n1 / n2,
		cosAlpha = -vector.dot(normal),
		sin2Alpha = 1 - cosAlpha*cosAlpha,
		sin2Omega = n*n * sin2Alpha,
		cosOmega = sqrt(1 - sin2Omega);
	return vector * n + normal * (n * cosAlpha - cosOmega);
}

const unsigned long vectorToColor(const Vec3 &vec) {
	unsigned int r, g, b;
	r = std::min((int)(vec.x * 255), 255);
	g = std::min((int)(vec.y * 255), 255);
	b = std::min((int)(vec.z * 255), 255);
	return (r | (g << 8) | (b << 16));
}