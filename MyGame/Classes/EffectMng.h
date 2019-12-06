#pragma once
#include <cocos2d.h>
#include "Effekseer/Effekseer.h"
#include <map>

#define lpEffectMng EffectMng::GetInstance()

class EffectMng
{
public:
	static EffectMng & GetInstance(void)
	{
		return *s_Instance;
	}
	~EffectMng();

	bool AddEffect(const std::string name, float extend, cocos2d::Vec2 pos, cocos2d::Vec3 rotate, efk::EffectManager* efMng);
	efk::EffectEmitter* GetEmitter(const std::string name);									// ´Ð¯À°‚ÌŽæ“¾
	void EmitterPlay(const std::string name, cocos2d::Vec2 pos, cocos2d::Vec3 rotate);		// »³ÝÄÞŠJŽn

private:
	EffectMng();
	std::map<std::string, efk::EffectEmitter*>emitter;
	std::unique_ptr<efk::EffectManager>_effecMng;


	static std::unique_ptr<EffectMng> s_Instance;
};

