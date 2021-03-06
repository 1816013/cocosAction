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
	void Init(void);															// CkInit()
	bool AddSound(std::string bank_p, std::string soundName, SOUND_TYPE type);	// »³έΔήΗΑ
	void Update(void);															// CkUpDate()
	void PlayBySoundName(std::string soundName);								// o^΅½»³έΔήπΌO©ηΔΆ·ι
	void ckEnd(void);															// »³έΔήIΉQ[IΉ
	void SetPauseAll(bool pauseF);												// »³έΔήπSΔκβ~

private:
	SoundMng();

	CkBank* _bank;
	std::map<std::string,CkSound*>_sound;

	static std::unique_ptr<SoundMng> s_Instance;
};

