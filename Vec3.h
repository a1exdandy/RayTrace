#ifndef _VEC3_H
#define _VEC3_H

class Vec3 {
public:
	double x, y, z;
	Vec3(double x, double y, double z);
	Vec3();
	double dot (const Vec3 &other) const;
	Vec3 operator - (const Vec3 &other) const;
	Vec3 operator + (const Vec3 &other) const;
	Vec3 & operator += (const Vec3 &other);
	Vec3 operator * (double k) const;
	Vec3 normalize() const;
	double abs() const;
private:
};

#endif