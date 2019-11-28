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

bool SoundMng::AddSound(std::string bank_p, std::string sound_name, SOUND_TYPE type)
{
	_bank = CkBank::newBank(bank_p.c_str(), kCkPathType_FileSystem);

	return false;
}
