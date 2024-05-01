#pragma once
#include "ResourceBase.h"

enum class SoundType
{
	BGM,
	Normal,
};

/*
	사운드와 관련된 부분은 직접 만들어볼 예정이므로 본문에는 포함하지 않는다.
*/
class Sound : public ResourceBase
{
public:
	Sound();
	virtual ~Sound();
	
	bool LoadWave(std::filesystem::path fullPath);
	void Play(bool loop = false);
	void Stop(bool reset = false);

private:
	virtual void LoadFile(const std::wstring& path) {}
	virtual void SaveFile(const std::wstring& path) {}

private:
	LPDIRECTSOUNDBUFFER _soundBuffer = nullptr;
	DSBUFFERDESC _bufferDesc = {};
};
