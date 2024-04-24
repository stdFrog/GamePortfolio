#pragma once

/*
	로컬 공간을 월드 공간으로 변환하는 모델링 행렬을 설계해봤다.
	이제 객체를 따라 다니는 카메라를 만들어볼 것이다.

	카메라는 자신이 출력할 화면의 해상도 정보를 가지고 월드의 일부를 그린다.
	곧, 이 정보를 뷰포트라고 부르는데 게임에 접속해서 유저가 보는 화면을 떠올릴 수 있다.

	모든 객체(또는 플레이어)는 자신만의 로컬 공간을 가지고 있으며,
	월드 공간에 재배치될 때 그 일부만을 화면에 그린다.
	
	기본적으로 각 객체는 자신을 기준으로 한 위치 정보를 가지고
	화면상에 꼭 필요한 부분만을 그려낼 수 있어야 하므로 카메라 오브젝트가 필요하다.

	카메라는 자신을 기준으로 담당하고 있는 물체의 월드 공간 좌표를 뷰 공간으로 변환한다.
	여기서 뷰 공간이란 말 그대로 보여줄 공간을 말한다.
	
	이는 곧, 월드 좌표(모델링 행렬)를 카메라 중심으로 다시 변환해야 한다는 의미이다.
	이때 사용되는 행렬을 뷰 행렬(V)이라 부르며, 계산 하는 방법도 그리 어렵지 않다.

	월드 공간의 원점을 기준으로 했을 때, 그려야 할 물체의 좌표와 카메라의 좌표를 구하고
	서로 빼면 된다. 
	
	더 정확히는, 월드 공간으로부터 카메라가 가지는 상대 좌표를 구해 그 거리만큼
	다른 오브젝트들의 위치에 더하기만 하면 된다.

	행렬을 사용할 때는 보통 이동 행렬의 역행렬을 구해 모델링 행렬에 곱하는 것으로
	이 처리를 끝낼 수 있다.
*/
class CameraObject
{
	RECT _ViewPort;
	Transform _Transform;

public:
	Transform& GetTransform() { return _Transform; }
	const Transform& GetTransform() const { return _Transform; }

public:
	RECT GetViewPortSize() { return _ViewPort; }
	void SetViewPortSize(RECT ViewPort) { _ViewPort = ViewPort; }

public:
	Matrix GetViewMatrix();

public:
	CameraObject();
	~CameraObject();
};

