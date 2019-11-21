#include "ActionMng.h"
#include "MoveLR.h"
#include "CheckKey.h"
#include "Colision.h"
#include "Fall.h"
#include "Jump.h"

USING_NS_CC;

ActionMng::ActionMng()
{
}


ActionMng::~ActionMng()
{
}

void ActionMng::AddActModule(const std::string & actName, actModule & module)
{
	if (actName == "ç∂à⁄ìÆ" || actName == "âEà⁄ìÆ")
	{
		_moduleMap.try_emplace(actName, std::move(module));
		_moduleMap[actName].act.emplace_back(CheckKey());
		_moduleMap[actName].act.emplace_back(Colision());
		_moduleMap[actName].runAction = MoveLR();
	}
	if (actName == "ºﬁ¨›Ãﬂ")
	{
		_moduleMap.try_emplace(actName, std::move(module));
		_moduleMap[actName].act.emplace_back(CheckKey());
		_moduleMap[actName].runAction = Jump();
	}
	if (actName == "ºﬁ¨›ÃﬂíÜ")
	{
		_moduleMap.try_emplace(actName, std::move(module));
		_moduleMap[actName].act.emplace_back(Colision());
		_moduleMap[actName].runAction = Jumping();
	}
	if (actName == "óéâ∫")
	{
		_moduleMap.try_emplace(actName, std::move(module));
		_moduleMap[actName].act.emplace_back(Colision());
		_moduleMap[actName].runAction = Fall();
	}
	/*if (actName == "óéâ∫íÜ")
	{
		_moduleMap.try_emplace(actName, std::move(module));
		
		_moduleMap[actName].runAction = Falling();
	}*/
}

void ActionMng::update(cocos2d::Sprite& sp)
{
	auto check = [this](Sprite& sp, actModule& module)
	{
		for (auto listModule : module.act/*= module.act.begin(); listModule == module.act.end(); ++listModule*/)
		{
			if (!listModule(sp, module))
			{	
				return false;
			}		
		}
		return true;
	};

	for (auto mapModule : _moduleMap)
	{
		if (check(sp, mapModule.second))
		{
			mapModule.second.runAction(sp, mapModule.second);
		}
	}
}
