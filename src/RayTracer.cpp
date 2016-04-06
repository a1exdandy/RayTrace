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
		if (dist < min_dist) {
			object = obj;
			min_dist = dist;
		}
	}

	// not intersection found
	if (object == NULL)
		return backgroundColor;

	bool innerIntersection = false;
	// intersection point
	Vec3 hit = point + (direction * min_dist);
	// normal to object in intersection point
	Vec3 nhit = object->getNormal(hit);
	if (direction.dot(nhit) > 0) {
		nhit = nhit * -1;
		innerIntersection = true;
	}

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
				double shininessCoefficient = lightRayReflected.dot(direction * -1);
				if (shininessCoefficient > 0) {
					specularColor += lightColor * pow(shininessCoefficient, object->getShininess()) * lightObj.getLightness();
				}
			}
			double diffuseCoefficient = lightRay.dot(nhit);
			if (diffuseCoefficient > 0)
				//diffuseColor = (diffuseColor + surfaceColor * diffuseCoefficient) * lightObj.getLightness();
				diffuseColor += surfaceColor * diffuseCoefficient * lightObj.getLightness();
		}
	}

	// calculate reflection and refraction color (Fresnel)
	double reflectivity = object->getReflectivity(),
		refractionIndex = object->getRefractionIndex();
	if (traceDepth > 0 && (reflectivity != NOT_REFLECTIVE || refractionIndex != NOT_REFRACTIVE)) {
		if (refractionIndex == NOT_REFRACTIVE) {
			Vec3 reflectedVector = reflect(direction * -1, nhit).normalize();
			reflectedColor = rayTrace(hit + reflectedVector * 1e-7, reflectedVector, objects, lights, traceDepth - 1) * reflectivity;
		}
		else {
			double n1 = refractionIndex,
				n2 = airRefractionIndex,
				n, reflectionCoefficient,
				refractionCoefficient,
				cosI, cosT, sinI2, sinT2, Rs, Rp;

			if (innerIntersection)
				std::swap(n1, n2);

			n = n1 / n2;
			cosI = -direction.dot(nhit);
			sinI2 = 1 - cosI*cosI;
			sinT2 = n*n * sinI2;
			cosT = sqrt(1 - sinT2);
			Rs = (n1 * cosI - n2 * cosT) / (n1 * cosI + n2 * cosT);
			Rp = (n2 * cosI - n1 * cosT) / (n2 * cosI + n1 * cosT);
			reflectionCoefficient = (Rs*Rs + Rp*Rp) / 2.0;

			refractionCoefficient = 1.0 - reflectionCoefficient;
			Vec3 refractedVector = (direction * n + nhit * (n * cosI - cosT)).normalize(),
				reflectedVector = reflect(direction * -1, nhit).normalize();
			reflectedColor = rayTrace(hit + reflectedVector * 1e-7, reflectedVector, objects, lights, traceDepth - 1) * reflectionCoefficient;
			refractedColor = rayTrace(hit + refractedVector * 1e-7, refractedVector, objects, lights, traceDepth - 1) * refractionCoefficient;
		}

	}

	return ambientColor + diffuseColor + specularColor + reflectedColor + refractedColor;
}

const Vec3 reflect(const Vec3 &vector, const Vec3 &normal) {
	return normal * vector.dot(normal) * 2.0 - vector;
}

const unsigned long vectorToColor(const Vec3 &vec) {
	unsigned int r, g, b;
	r = std::min((int)(vec.x * 255), 255);
	g = std::min((int)(vec.y * 255), 255);
	b = std::min((int)(vec.z * 255), 255);
	return (r | (g << 8) | (b << 16));
}