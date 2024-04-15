#pragma once

class Vector
{
public:
	static const Vector UnitX;
	static const Vector UnitY;
	static const Vector Zero;
	static const Vector One;

	float x, y;

public:
	Vector(const float X = 0.f, const float Y = 0.f) : x(X), y(Y) { ; }
	Vector(const Vector& Other = Vector::Zero) : x(Other.x), y(Other.y) { ; }

public:
	Vector operator -() const {
		return Vector(-x, -y);
	}

	Vector operator +(const float& Value) const {
		return Vector(x + Value, y + Value);
	}

	Vector& operator +=(const float& Value) {
		x += Value;
		y += Value;

		return *this;
	}

	Vector operator +(const Vector& Other) const {
		return Vector(x + Other.x, y + Other.y);
	}

	Vector& operator +=(const Vector& Other) {
		x += Other.x;
		y += Other.y;

		return *this;
	}

	Vector operator *(const float& Value) const {
		return Vector(x * Value, y * Value);
	}

	Vector& operator *=(const float& Value) {
		x *= Value;
		y *= Value;

		return *this;
	}

	Vector operator *(const Vector& Other) const {
		return Vector(x * Other.x, y * Other.y);
	}

	Vector& operator *=(const Vector& Other) {
		x *= Other.x;
		y *= Other.y;

		return *this;
	}

	Vector operator -(const float& Value) const {
		return Vector(x - Value, y - Value);
	}

	Vector& operator -=(const float& Value) {
		x -= Value;
		y -= Value;

		return *this;
	}

	Vector operator -(const Vector& Other) const {
		return Vector(x - Other.x, y - Other.y);
	}

	Vector& operator -=(const Vector& Other) {
		x -= Other.x;
		y -= Other.y;

		return *this;
	}

	Vector operator /(const float& Value) const {
		return Vector(x / Value, y / Value);
	}

	Vector& operator /=(const float& Value) {
		x /= Value;
		y /= Value;

		return *this;
	}

	Vector operator /(const Vector& Other) const {
		return Vector(x / Other.x, y / Other.y);
	}

	Vector& operator /=(const Vector& Other) {
		x /= Other.x;
		y /= Other.y;

		return *this;
	}

	float Dot(const Vector& Other) const {
		return x * Other.x + y * Other.y;
	}

	Vector Cross(const Vector& Other) const {
		return Vector(y * Other.x, x * Other.y);
	}

	float Squared() const {
		return x * x + y * y;
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

		return Vector(x, y) * GameMath::rSqrt(len);
	}
};

