#include "ActionMng.h"
#include <Unit/Player.h>
#include "CheckList.h"
#include "CheckKey.h"
#include "Colision.h"
#include "MoveLR.h"
#include "Fall.h"
#include "Jump.h"
#include "ChangeLR.h"
#include "Shot.h"

USING_NS_CC;

ActionMng::ActionMng()
{
}


ActionMng::~ActionMng()
{
}

void ActionMng::AddActModule(const std::string & actName, actModule & module)
{
	if (_moduleMap.find(actName) == _moduleMap.end())
	{
		if (actName == "ç∂à⁄ìÆ" || actName == "âEà⁄ìÆ")
		{
			_moduleMap.emplace(actName, std::move(module));
			_moduleMap[actName].act.emplace_back(CheckList());
			_moduleMap[actName].act.emplace_back(CheckKey());
			_moduleMap[actName].act.emplace_back(Colision());
			_moduleMap[actName].runAction = MoveLR();
		}
		if (actName == "óéâ∫")
		{
			_moduleMap.emplace(actName, std::move(module));
			_moduleMap[actName].act.emplace_back(CheckList());
			_moduleMap[actName].act.emplace_back(Colision());
			_moduleMap[actName].runAction = Fall();
		}
		if (actName == "óéâ∫íÜ")
		{
			_moduleMap.emplace(actName, std::move(module));
			_moduleMap[actName].act.emplace_back(CheckList());
			_moduleMap[actName].act.emplace_back(Colision());
			_moduleMap[actName].runAction = Falling();
		}
		if (actName == "ºﬁ¨›Ãﬂ")
		{
			_moduleMap.emplace(actName, std::move(module));
			_moduleMap[actName].act.emplace_back(CheckList());
			_moduleMap[actName].act.emplace_back(CheckKey());
			_moduleMap[actName].runAction = Jump();
		}
		if (actName == "ºﬁ¨›ÃﬂíÜ")
		{
			_moduleMap.emplace(actName, std::move(module));
			_moduleMap[actName].act.emplace_back(CheckList());
			_moduleMap[actName].act.emplace_back(Colision());
			_moduleMap[actName].runAction = Jumping();
		}
		if (actName == "âEå¸Ç´" || actName == "ç∂å¸Ç´")
		{
			_moduleMap.emplace(actName, std::move(module));
			_moduleMap[actName].act.emplace_back(CheckList());
			_moduleMap[actName].act.emplace_back(CheckKey());
			_moduleMap[actName].runAction = ChangeLR();
		}
		if (actName == "ºÆØƒ")
		{
			_moduleMap.emplace(actName, std::move(module));
			_moduleMap[actName].act.emplace_back(CheckList());
			_moduleMap[actName].act.emplace_back(CheckKey());
			_moduleMap[actName].runAction = Shot();
		}
	}
}

void ActionMng::update(cocos2d::Sprite& sp)
{
	auto check = [this](Sprite& sp, actModule& module)
	{
		for (auto listModule : module.act)
		{
			if (!listModule(sp, module))
			{
				return false;
			}
		}
		return true;
	};

	bool actFlag = false;
	for (auto mapModule : _moduleMap)
	{
		if (check(sp, mapModule.second))
		{
			if (mapModule.second.runAction(sp, mapModule.second))
			{
				((Player&)sp).ActState(mapModule.second.actID);
				actFlag = true;
			}
		}
	}
	if (actFlag == false)
	{
		((Player&)sp).ActState(ACT_STATE::IDLE);
	}

}
