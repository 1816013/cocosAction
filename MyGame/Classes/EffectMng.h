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
	efk::EffectEmitter* GetEmitter(const std::string name);

private:
	EffectMng();
	std::map<std::string, efk::EffectEmitter*>emitter;
	static std::unique_ptr<EffectMng> s_Instance;
};

