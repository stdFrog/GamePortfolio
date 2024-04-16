#pragma once

class Vector
{
public:
	static const Vector UnitX;
	static const Vector UnitY;
	static const Vector UnitZ;
	static const Vector Zero;
	static const Vector One;

	float x, y, z;

public:
	Vector(const float X = 0.f, const float Y = 0.f, const float Z = 0.f) : x(X), y(Y), z(Z){ ; }
	Vector(const Vector& Other = Vector::Zero) : x(Other.x), y(Other.y), z(Other.z) { ; }

public:
	Vector operator -() const {
		return Vector(-x, -y, -z);
	}

	Vector operator +(const float& Value) const {
		return Vector(x + Value, y + Value, z + Value);
	}

	Vector& operator +=(const float& Value) {
		x += Value;
		y += Value;
		z += Value;

		return *this;
	}

	Vector operator +(const Vector& Other) const {
		return Vector(x + Other.x, y + Other.y, z + Other.z);
	}

	Vector& operator +=(const Vector& Other) {
		x += Other.x;
		y += Other.y;
		z += Other.z;

		return *this;
	}

	Vector operator *(const float& Value) const {
		return Vector(x * Value, y * Value, z * Value);
	}

	Vector& operator *=(const float& Value) {
		x *= Value;
		y *= Value;
		z *= Value;

		return *this;
	}

	Vector operator *(const Vector& Other) const {
		return Vector(x * Other.x, y * Other.y, z * Other.z);
	}

	Vector& operator *=(const Vector& Other) {
		x *= Other.x;
		y *= Other.y;
		z *= Other.z;

		return *this;
	}

	Vector operator -(const float& Value) const {
		return Vector(x - Value, y - Value, z - Value);
	}

	Vector& operator -=(const float& Value) {
		x -= Value;
		y -= Value;
		z -= Value;

		return *this;
	}

	Vector operator -(const Vector& Other) const {
		return Vector(x - Other.x, y - Other.y, z- Other.z);
	}

	Vector& operator -=(const Vector& Other) {
		x -= Other.x;
		y -= Other.y;
		z -= Other.z;

		return *this;
	}

	Vector operator /(const float& Value) const {
		return Vector(x / Value, y / Value, z / Value);
	}

	Vector& operator /=(const float& Value) {
		x /= Value;
		y /= Value;
		z /= Value;

		return *this;
	}

	Vector operator /(const Vector& Other) const {
		return Vector(x / Other.x, y / Other.y, z / Other.z);
	}

	Vector& operator /=(const Vector& Other) {
		x /= Other.x;
		y /= Other.y;
		z /= Other.z;

		return *this;
	}

	float Dot(const Vector& Other) const {
		return x * Other.x + y * Other.y + z * Other.z;
	}

	Vector Cross(const Vector& Other) const {
		return Vector(y * Other.z - z * Other.y, z * Other.x - x * Other.z, x * Other.y - y * Other.x);
	}

	float Squared() const {
		return x * x + y * y + z * z;
	}

	float length() const {
		return GameMath::Sqrt(Squared());
	}

	void Normalize() {
		*this = GetNormalize();
	}

	Vector GetNormalize() const {
		float len = length();

		if (len == 1.f) {
			return *this;
		}
		else if (len == 0.f) {
			return Vector::Zero;
		}

		return Vector(x, y, z) * GameMath::rSqrt(len);
	}
};

