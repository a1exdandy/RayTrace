#include "Object.h"

Object::Object(double shininess, double reflectivity, double refractionIndex) 
	: shininess(shininess), 
	reflectivity(reflectivity), 
	refractionIndex(refractionIndex) {}

const double Object::getReflectivity() const {
	return reflectivity;
}

const double Object::getRefractionIndex() const {
	return refractionIndex;
}

const double Object::getShininess() const {
	return shininess;
}