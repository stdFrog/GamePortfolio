#pragma once
const int DIMENSION = 3;
/*
	행렬은 선형 변환의 계산 과정을 체계화하여 손쉽게 계산할 수 있는 편리한 도구이다.

	여기서 선형 변환이란, 순수한 비로 구성된 1차적 대응 관계에 있는 변환을 말한다.
	곧, 평행이동을 떠올리면 쉽게 이해할 수 있다.

	선형 변환은 선형 함수를 의미하며 이는 1차 동차성과 가법성을 만족하는 함수를 말한다.
	아래를 보자.

	좌변: f(x1 + x2)	= f(x1) + f(x2)		( 가법성 )
	우변: f(k * x)		= k * f(x)			( 1차 동차성 )

	이 두 함수는 선형성을 만족하는가를 판단할 때 사용된다.

	예로, y = ax의 그래프를 떠올려보자.
	이 직선은 f(x) = ax의 함수로 볼 수 있다. 이 함수의 인자로 x1 + x2를 대입한 후 
	좌변과 우변의 결과가 서로 같다면 가법성을 만족한다고 할 수 있다.

	-> 좌변 : f(x1 + x2)	= a(x1 + x2)	-> 우변 : f(x1) + f(x2)		= ax1 + ax2
	∴ a(x1 + x2) = ax1 + ax2
	
	또, k * x를 대입하여 좌변과 우변이 서로 같다면 1차 동차성을 만족한다고 할 수 있다.
	
	-> 좌변 : f(k * x)		= a(k * x)		-> 우변 : k * f(x)			= k(a * x)
	∴ a(k * x) = k(a * x)
*/
class Matrix
{
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