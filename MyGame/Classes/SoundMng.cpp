#include "SoundMng.h"
#include <ck/ck.h>
#include <ck/config.h>

std::unique_ptr<SoundMng>SoundMng::s_Instance(new SoundMng);

SoundMng::SoundMng()
{
}

SoundMng::~SoundMng()
{

}

void SoundMng::Init(void)
{
#if CK_PLATFORM_ANDROID
	CkConfig config(env, activity);
#else
	CkConfig config;
#endif
	CkInit(&config);
}

bool SoundMng::AddSound(std::string bank_p, std::string soundName, SOUND_TYPE type)
{
	_bank = CkBank::newBank(bank_p.c_str(), kCkPathType_FileSystem);
	if (_bank == nullptr)
	{
		return false;
	}
	if (_sound.find(soundName) != _sound.end())
	{

	}

	return true;
}
