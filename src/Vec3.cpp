#include "Vec3.h"
#include <cmath>

Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

Vec3::Vec3() : x(0), y(0), z(0) {}

double Vec3::dot(const Vec3 &other) const {
	return x*other.x + y*other.y + z*other.z;
}

Vec3 Vec3::operator - (const Vec3 &other) const {
	return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator + (const Vec3 &other) const {
	return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 & Vec3::operator += (const Vec3 &other){
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}


Vec3 Vec3::operator * (double k) const {
	return Vec3(x*k, y*k, z*k);
}

double Vec3::abs() const {
	return sqrt(x*x + y*y + z*z);
}

Vec3 Vec3::normalize() const {
	return *this * (1/abs());
}