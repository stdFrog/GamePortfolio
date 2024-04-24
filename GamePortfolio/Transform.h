#pragma once

/*
	현재 프로젝트에선 아핀 공간을 포함한 3차원 좌표계를 사용하고 있다.

	굳이 행렬을 사용하지 않을 생각이라면 이러한 아핀 공간은 필요없다.
	다만, 실습 및 학습을 목적으로 하므로 행렬이란 도구도 사용해보려 한다.

	나중에서야 할 이야기이지만, 게임 구조가 커질 수록 이런 직접 연산 과정을 작성하는 것은
	개발에 굉장히 불리하다. 즉, 개발 비용이 증가한다.
	
	실습이니 행렬과 직접 연산 두 가지 모두 해보는 것으로 하자.

	이 클래스는 씬에 등장하는 각 객체마다 배치될 것이다.
	곧, 해당 객체의 여러 변환 상태를 가지며 최종 모델링 행렬에 반드시 추가되어야 할
	정보를 가지고 있다.
*/

/*
	이 클래스를 만들 때 Vector 클래스를 3차원으로 확장할 필요가 있다.
	
	이유는 비교적 간단한데 이동 변환이 불가능하기 때문이다.
	이동 변환이 불가능한 이유는 선형성을 만족하지 못하기 때문이며 이는 곧, 선형 독립 관계를
	유지하지 못한다는 뜻이다.

	여기서 선형성이란, 예측 가능한 비례 관계를 말한다.
	곧, 두 집합이 순수한 비 만으로 구성되어 1차적 대응 관계를 가져야 한다는 뜻이다.

	그런데 벡터 공간에서 이 조건을 만족하려면 반드시 필요한 전제가 있다.
	곧, 필요 조건으로써 존재하는데 대부분 크게 신경 쓰지 않는다.

	결론만 말하면, 벡터 공간에서의 선형성은 벡터가 원점으로부터 출발한다는 것을 전제로 한다.

	쉽게 이해되지 않는다면 기저 집합에 속한 벡터 즉, 선형 독립의 관계를 가지는
	벡터 한 쌍을 떠올리면 된다.

	모든 벡터는 언제나 표준기저벡터(e1, e2, ...)로부터 생성되고,
	이렇게 생성된 벡터들은 서로 평행하며 이를 잇는 수직선을 그려보면 언제나 원점을 지나는
	직선이 그려진다.
	
	2x2크기의 정방행렬에서 이동 변환은 이러한 표준기저벡터를 변화시키므로
	변환 행렬을 만드는 것이 불가능하다.

	그렇다면 어떻게 해야 할까?
	전단 변환 행렬을 떠올려보면 의외로 쉽게 답을 찾을 수 있다.
	아래와 같은 2x2 크기의 정방행렬이 있다고 가정해보자.

		 x  y

	x	[1][0]
	y	[0][1]

	전단 변환은 임의의 범위만큼 밀어내는 동작을 한다.

	곧, 두 개의 벡터를 가지는 행렬에서 하나의 벡터를 표준기저벡터 e2(0,1)로 잡고
	다른 하나에 일정한 힘을 가함으로써 임의의 범위만큼 밀어내는 동작이며,
	이를 굳이 행렬로 나타내보면 다음과 같다.

	[1][a]		[x]				[x + a]
	[0][1]	*	[1]		=		[  1  ]

	y값을 1로 고정한 후 단순히 x값에 a만큼의 값을 추가한 것과 같다.
	그런데 이를 1차원에서 해석해보면 어떨까?

	위 동작이 곧, 1차원에서의 이동 변환이 되며 이 원리를 2차원에서도 적용할 수 있다.
	이를 위해 벡터를 한 차원 늘리는데 이렇게 늘어난 공간을 활용하면 이동 변환을 쉽게
	행렬을 이용해 구현할 수 있다.
	
	참고로, 이를 위해 늘린 부분 공간을 아핀 공간이라 부르는데,
	이처럼 벡터의 선형 변환에 아핀 공간을 활용한 경우, 아핀 변환이란 또 다른 명칭이 있다.
	
	아래 트랜스폼 클래스는 이 아핀 공간을 적용해 각 객체가 고유의 좌표를 가지게 하여
	사용자가 각 객체를 월드 공간에 배치하기 쉽게 만든다.

	변환에 필요한 정보를 각 객체가 소유하므로 적당한 변환을 통해 월드 공간의 정보로 바꿀 수 있다.
*/
class Transform
{
	Vector _Position = Vector::Zero;
	Vector _Scale = Vector::One;
	Vector _Right = Vector::UnitX;
	Vector _Up = Vector::UnitY;

	float _Rotation;

private:
	void Update();

public:
	Matrix GetModelingMatrix() const;

public:
	Vector GetPosition() const { return _Position; }
	Vector GetScale() const { return _Scale; }
	const Vector& GetLocalX() const { return _Right; }
	const Vector& GetLocalY() const { return _Up; }

	float GetCurrentDeg() { return _Rotation; }

public:
	void SetPosition(const Vector& Position) { _Position = Position; }
	void SetRotation(const float& Degree) { _Rotation = Degree; Update(); }
	void SetScale(const Vector& Scale) { _Scale = Scale; }

public:
	void AddPosition(const Vector& Position) { _Position += Position; }
	void AddRotation(const float& Degree) { _Rotation += Degree; Update(); }

public:
	Transform();
	~Transform();
};