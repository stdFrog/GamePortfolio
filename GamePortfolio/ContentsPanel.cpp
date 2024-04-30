#include "pch.h"
#include "ContentsPanel.h"
#include "ContentsButton.h"

/*
	예시를 보면 여태 초기화 함수를 따로 선언해 필요한 처리를 해왔다.
	그런데, 이 클래스에선 컨텐츠측의 자동화를 위해 생성자를 활용한다.

	곧, 일관되지 않은 초기화 처리로 인해 로직이 꼬일 수 있으며, 실제로도 꼬인다.
	
	현재 프로젝트에선 예시와 달리 매니저 클래스를 사용하지 않고 상속 설계 구조를 십분 활용한다.
*/
ContentsPanel::ContentsPanel(BaseScene* CurrentScene) : Panel(CurrentScene) {
	/*
		패널이 배치될 씬을 매개변수로 전달받는 것은 논리적으로 전혀 이상하지 않다.
		다만, 컨텐츠측의 부담을 덜고 싶다면 매니저 클래스를 활용하는 것이 좋다.

		이 클래스를 보면 리소스 매니저의 장점을 알 수 있다.
	*/
	const auto& Scene = dynamic_cast<BaseScene*>(_Owner);
	const auto& Engine = (GameEngine*)Scene->GetInstance();

	/*
		임시 클래스이므로 생성 및 삭제 함수는 따로 만들지 않는다.
	*/
	{
		Button* NewInterface = new Button();
		NewInterface->SetPosition(Vector(400, 200));
		NewInterface->SetSize(Vector(650, 300));
		NewInterface->SetOwner(this);
		AddChild(NewInterface);
	}
	{
		Button* NewInterface = new Button();
		NewInterface->SetSprite(Engine->GetSprite(L"Start_Off"), BS_DEFAULT);
		NewInterface->SetSprite(Engine->GetSprite(L"Start_On"), BS_CLICKED);
		NewInterface->SetOwner(this);
		NewInterface->SetPosition(Vector(200, 200));

		NewInterface->AddOnClickDelegate(this, &ContentsPanel::OnClickStartButton);
		AddChild(NewInterface);
	}
	{
		Button* NewInterface = new Button();
		NewInterface->SetSprite(Engine->GetSprite(L"Edit_Off"), BS_DEFAULT);
		NewInterface->SetSprite(Engine->GetSprite(L"Edit_On"), BS_CLICKED);
		NewInterface->SetOwner(this);
		NewInterface->SetPosition(Vector(400, 200));

		NewInterface->AddOnClickDelegate(this, &ContentsPanel::OnClickEditButton);
		AddChild(NewInterface);
	}
	{
		Button* NewInterface = new Button();
		NewInterface->SetSprite(Engine->GetSprite(L"Exit_Off"), BS_DEFAULT);
		NewInterface->SetSprite(Engine->GetSprite(L"Exit_On"), BS_CLICKED);
		NewInterface->SetOwner(this);
		NewInterface->SetPosition(Vector(600, 200));

		NewInterface->AddOnClickDelegate(this, &ContentsPanel::OnClickExitButton);
		AddChild(NewInterface);
	}
}

ContentsPanel::~ContentsPanel() {

}

void ContentsPanel::OnClickStartButton() {
	
}

void ContentsPanel::OnClickEditButton() {

}

void ContentsPanel::OnClickExitButton() {
	
}

BOOL ContentsPanel::Initilaize() {
	Super::Initialize();

	return TRUE;
}

void ContentsPanel::Update(float dtSeconds) {
	Super::Update(dtSeconds);
}

void ContentsPanel::Render(HDC hDC) {
	Super::Render(hDC);

	std::wstring str = std::format(L"Count : {0}", _Count);
	_TEXTOUT(hDC, 100, 0, str.c_str());
}
