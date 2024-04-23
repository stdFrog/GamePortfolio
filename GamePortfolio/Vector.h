#pragma once

/*
	벡터란,

	평면을 구성하는 원소를 말한다.
	두 개 이상의 실수를 곱집합으로 묶어 형성한 집합을 공리적 집합론의 관점에서
	벡터 공간이라 부르고, 이 공간의 원소를 벡터라 부른다.

	여기서 평면이란,
	실수 집합이 곱집합으로 묶여 형성된 또 다른 집합을 말하며,
	곧, 실수로 이루어진 직선(수직선) 두 개가 서로 수직할 때 나타나는 공간을 말한다.
	
	정리하면, 벡터 공간과 평면은 같은 특성을 가진 원소로 이루어져 있다.

	따라서 평면과 벡터 공간을 구분짓지 않고 쉽게 평면이라 부르기로 한다.
	
	벡터는 시각적인 표현을 위해 반드시 필요하다.
	벡터는 곧, 그 위치에 점을 찍어 표현하는데 이 점이 모여 물체를 이루므로 평면에서 무언가를
	표현하고자 한다면, 이에 대한 공부가 선행되어야 한다.
*/

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

