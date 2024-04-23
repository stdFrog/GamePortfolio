#pragma once

/*
	선형대수에서 선형성은 예측/계산 가능한 비례 관계를 말한다.
	평면에서 이러한 성질을 가진 직선은 다음과 같은 조건을 만족한다.

	좌변은 f(x1 + x2) = f(x1) + f(x2)	: 가법성
	우변은 f(k * x) = k * f(x)			: 1차 동차성

	이 둘은 선형성을 만족하는가를 판단할 때 즉, 명제를 증명할 때 사용된다.

	예로, y = ax의 그래프를 떠올려보자.
	이 직선은 f(x) = ax의 함수로 볼 수 있다. 이 함수의 인자로 x1 + x2를 대입한 후 
	좌변과 우변의 결과가 서로 같다면 가법성을 만족한다고 할 수 있다.

	또, k * x를 대입하여 좌변과 우변이 서로 같다면 1차 동차성을 만족한다고 할 수 있다.

	적용해보면 다음과 같다.
	-> 좌변 : f(x1 + x2) = a(x1 + x2)
	-> 우변 : f(x1) + f(x2) = ax1 + ax2
	
	-> 좌변 : f(k * x) = a(k * x)
	-> 우변 : k * f(x) = k * (a * x)

	이러한 함수를 선형 함수라고 한다.
	흔히 아는 y = x^2, y = x^3과 같이 우함수 또는 기함수 등을 떠올리면 된다.
	단, y = ax + b와 같이 bias(절편)를 가진 함수는 이러한 조건을 만족하지 못한다.

	따라서 선형성을 가진 직선은 원점을 지난다는 특징을 가지며 순수한 비(ratio)로 구성된 1차적 대응 관계를 의미한다.
	
*/

const int DIMENSION = 3;

class Matrix
{
	// 모델링 행렬은 나중에 추가해보자.
public:
	std::array<Vector, DIMENSION> Columns = {
		Vector::UnitX,
		Vector::UnitY,
		Vector::UnitZ
	};

	Matrix(
		const Vector& v1 = Vector::UnitX,
		const Vector& v2 = Vector::UnitY,
		const Vector& v3 = Vector::UnitZ
	) {
		Columns = { v1, v2, v3 };
	}

	Vector& operator [](const int Index) {
		return Columns[Index];
	}

	const Vector& operator [](const int Index) const {
		return Columns[Index];
	}

	Matrix Transpose() const {
		return Matrix(
			Vector(Columns[0].x, Columns[1].x, Columns[2].x),
			Vector(Columns[0].y, Columns[1].y, Columns[2].y),
			Vector(Columns[0].z, Columns[1].z, Columns[2].z)
		);
	}

	Vector operator *(const Vector& Other) const {
		Matrix Temp = Transpose();

		return Vector(
			Temp[0].Dot(Other),
			Temp[1].Dot(Other),
			Temp[2].Dot(Other)
		);
	}

	Matrix operator *(const Matrix& Other) const {
		Matrix Temp = Transpose();

		return Matrix(
			Vector(
				Temp[0].Dot(Other[0]),
				Temp[1].Dot(Other[0]),
				Temp[2].Dot(Other[0])
			),
			Vector(
				Temp[0].Dot(Other[1]),
				Temp[1].Dot(Other[1]),
				Temp[2].Dot(Other[1])
			),
			Vector(
				Temp[0].Dot(Other[2]),
				Temp[1].Dot(Other[2]),
				Temp[2].Dot(Other[2])
			)
		);
	}
};