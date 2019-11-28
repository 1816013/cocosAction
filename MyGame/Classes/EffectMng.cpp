#include "EffectMng.h"

std::unique_ptr<EffectMng>EffectMng::s_Instance(new EffectMng);

EffectMng::EffectMng()
{
	
}

EffectMng::~EffectMng()
{

}

bool EffectMng::AddEffect(const std::string name, float extend, cocos2d::Vec2 pos, cocos2d::Vec3 rotate, efk::EffectManager* efMng)
{
	auto effect = efk::Effect::create(name, extend);
	if (emitter.find(name) == emitter.end())
	{
		emitter.emplace(name, efk::EffectEmitter::create(efMng));
		emitter[name]->setEffect(effect);
		emitter[name]->setPlayOnEnter(false);
		emitter[name]->setRotation3D(rotate);
		emitter[name]->setPosition(pos);
	}
	return true;
}

efk::EffectEmitter* EffectMng::GetEmitter(const std::string name)
{
	if (emitter.find(name) != emitter.end())
	{
		return emitter[name];
	}
	return nullptr;
}
