#pragma once
#include <cocos2d.h>
#include <ck/bank.h>
#include <ck/sound.h>

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

	bool AddSound(std::string bank_p, std::string sound_name, SOUND_TYPE type);

private:
	SoundMng();

	CkBank* _bank;
	std::map<std::string,CkSound*>_sound;

	static std::unique_ptr<SoundMng> s_Instance;
};

