#pragma once


class SoundManager
{
private:
	SoundManager() {}
	~SoundManager() {}

private:
	LPDIRECTSOUND _soundDevice = nullptr;

public:
	static SoundManager* GetInstance() {
		static SoundManager _Instance;
		return &_Instance;
	}

public:
	void Init(HWND hwnd);

	void Play(const std::wstring& key, bool loop = false);

	LPDIRECTSOUND GetSoundDevice() { return _soundDevice; }
};

