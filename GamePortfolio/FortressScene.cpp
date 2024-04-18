#include "pch.h"
#include "FortressScene.h"

FortressScene::FortressScene() {

}

FortressScene::~FortressScene() {

}

BOOL FortressScene::Initialize() {
	Player* P1, *P2;

	P1 = CreateObject<Player>();
	P2 = CreateObject<Player>();

	if (P1) {
		P1->SetPlayerType(PlayerType::MissileTank);
		P1->SetPosition(Vector(100, 400));
		P1->SetPlayerID(0);
		P1->SetPlayerTurn(TRUE);
		AppendObject(P1);

		_PlayerCount++;
	}

	if (P2) {
		P2->SetPlayerType(PlayerType::CanonTank);
		P2->SetPosition(Vector(700, 400));
		P2->SetPlayerID(1);
		P2->SetPlayerTurn(FALSE);
		AppendObject(P2);
		_PlayerCount++;
	}

	_TurnObject = 1;
	ChangePlayerTurn();
	
	return UI.Initialize(_EngineInstance);
}

void FortressScene::Update(float dtSeconds) {
	for (int i = 0; i < _Objects.size(); i++) {
		_Objects[i]->Update(dtSeconds);
	}

	/* 
	본래 Fortress 클래스는 UI만을 담당해야 한다.
	하지만, 큰 규모의 게임이 아니기 때문에 컨텐츠, UI 등의 담당 클래스를 따로 만들지 않고
	하나의 클래스에서 이러한 데이터를 공통으로 유지 관리하도록 한다.
	*/
	_SumTime += dtSeconds;
	if (_SumTime >= 1.f) {
		_SumTime = 0.f;

		int Time = UI.GetRemainTime();
		Time = max(0, Time - 1);

		UI.SetRemainTime(Time);
		if (Time == 0) {
			ChangePlayerTurn();
		}
	}
}

void FortressScene::Render(HDC hDC) {
	UI.Render(hDC);

	for (int i = 0; i < _Objects.size(); i++) {
		_Objects[i]->Render(hDC);
	}
}

void FortressScene::ChangePlayerTurn() {
	_TurnObject = (_TurnObject + 1) % _PlayerCount;

	for (int i=0; i<_Objects.size(); i++){
		auto Type = _Objects[i]->GetObjectType();
		if (Type != ObjectType::Player) {
			continue;
		}

		Player* player = static_cast<Player*>(_Objects[i]);
		if (player->GetPlayerID() == _TurnObject) {
			player->SetPlayerTurn(TRUE);
		}
		else {
			player->SetPlayerTurn(FALSE);
		}

		UI.SetRemainTime(10);
		UI.SetStaminaPercent(100.f);
		UI.SetPowerPercent(0.f);
		UI.SetWindPercent(static_cast<float>(-100 + rand() % 200));
	}
}