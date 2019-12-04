#include "EffectMng.h"

std::unique_ptr<EffectMng>EffectMng::s_Instance(new EffectMng);

EffectMng::EffectMng()
{
	
}

EffectMng::~EffectMng()
{
	/*for (auto name : emitter)
	{
		emitter[name.first]->release();
	}*/
}

bool EffectMng::AddEffect(const std::string name, float extend, cocos2d::Vec2 pos, cocos2d::Vec3 rotate, efk::EffectManager* efMng)
{
	auto effect = efk::Effect::create(name, extend);
	if (emitter.find(name) == emitter.end())
	{
		emitter.emplace(name, efk::EffectEmitter::create(efMng));
		emitter[name]->setEffect(effect);
		emitter[name]->setPlayOnEnter(false);
		//emitter[name]->retain();
		/*emitter[name]->setRotation3D(rotate);
		emitter[name]->setPosition(pos);*/
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

void EffectMng::EmitterPlay(const std::string name, cocos2d::Vec2 pos, cocos2d::Vec3 rotate)
{
	if (emitter.find(name) != emitter.end())
	{
		emitter[name]->setRotation3D(rotate);
		emitter[name]->setPosition(pos);
		emitter[name]->play();
	}
}

void EffectMng::EffectVisit(cocos2d::Renderer* renderer,cocos2d::Node& node, bool beginF)
{
	if (beginF)
	{
		_effecMng->begin(renderer, node.getGlobalZOrder());
	}
	else
	{
		_effecMng->end(renderer, node.getGlobalZOrder());
	}
}
