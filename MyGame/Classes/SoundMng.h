#pragma once
#include <cocos2d.h>
#include <ck/ck.h>
#include <ck/config.h>
#include <ck/bank.h>
#include <ck/sound.h>

#define lpSoundMng SoundMng::GetInstance()


enum SOUND_TYPE
{
	SE,
	BGM
};

class SoundMng
{
public:
	static SoundMng & GetInstance(void)
	{
		return *s_Instance;
	}
	~SoundMng();
	void Init(void);		// CkInit()
	bool AddSound(std::string bank_p, std::string soundName, SOUND_TYPE type);	// 
	void Update(void);
	void PlayBySoundName(std::string soundName);
	void ckEnd(void);
	void SetPauseAll(bool pauseF);

private:
	SoundMng();

	CkBank* _bank;
	std::map<std::string,CkSound*>_sound;

	static std::unique_ptr<SoundMng> s_Instance;
};

