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

	bool AddEffect(const std::string name, float extend, efk::EffectManager* efMng);
	efk::EffectEmitter* GetEmitter(const std::string name);									// ｴﾐｯﾀｰの取得
	void EmitterPlay(const std::string name, cocos2d::Vec2 pos, cocos2d::Vec3 rotate);		// ｻｳﾝﾄﾞ開始

private:
	EffectMng();
	std::map<std::string, efk::EffectEmitter*>emitter;
	std::unique_ptr<efk::EffectManager>_effecMng;


	static std::unique_ptr<EffectMng> s_Instance;
};

