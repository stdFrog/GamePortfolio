#include "pch.h"
#include "FlipbookActor.h"

FlipbookActor::FlipbookActor(ObjectType Type) : Actor(Type), _Flipbook(NULL) {

}

FlipbookActor::~FlipbookActor() {

}

BOOL FlipbookActor::Initialize() {
	Super::Initialize();

	return TRUE;
}

void FlipbookActor::Update(float dtSeconds) {
	Super::Update(dtSeconds);

	if (_Flipbook == NULL) { return; }

	const FlipbookInfo I = _Flipbook->GetInfo();
	if (I.loop <= FALSE && _Index == I.end) { return; }

	_Time += dtSeconds;
	int FrameCount = (I.end - I.start) + 1;
	float Delta = I.duration / FrameCount;

	if (_Time >= Delta) {
		_Time = 0.f;
		_Index = (_Index + 1) % FrameCount;
	}
}

void FlipbookActor::Render(HDC hDC) {
	Super::Render(hDC);

	if (_Flipbook == NULL) { return; }

	const FlipbookInfo I = _Flipbook->GetInfo();
	const auto& Scene = dynamic_cast<DevScene*>(_Scene);
	Vector CameraPosition = Scene->GetMainCamera().GetTransform().GetPosition();

	// 트랜스폼 정보를 사용하지 않았을 때(FlipbookActor)
	LONG Width, Height;
	WindowsUtility::GetWindowSize(GetForegroundWindow(), &Width, &Height);

	TransparentBlt(
		hDC,
		static_cast<int>(_Position.x - I.size.x / 2 - (CameraPosition.x - (Width - 264) / 2)),
		static_cast<int>(_Position.y - I.size.y / 2 - (CameraPosition.y - Height / 2)),
		static_cast<int>(I.size.x),
		static_cast<int>(I.size.y),
		I.texture->GetTextureDC(),
		static_cast<int>((I.start + _Index) * I.size.x),
		static_cast<int>(I.line * I.size.y),
		static_cast<int>(I.size.x),
		static_cast<int>(I.size.y),
		I.texture->GetTransParent()
		);
}

void FlipbookActor::SetFlipbook(Flipbook* NewFlipbook) {
	if (NewFlipbook && _Flipbook == NewFlipbook) { return; }

	_Flipbook = NewFlipbook;
	Reset();
}

void FlipbookActor::Reset() {
	_Time = 0.f;
	_Index = 0;
}

BOOL FlipbookActor::IsAnimationEnded() {
	if (_Flipbook == NULL) { return TRUE; }

	const FlipbookInfo& Info = _Flipbook->GetInfo();
	if (Info.loop == FALSE && _Index == Info.end) { return TRUE; }

	return FALSE;
}