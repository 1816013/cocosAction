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
		if (actName == "左移動" || actName == "右移動")
		{
			_moduleMap.emplace(actName, std::move(module));
			_moduleMap[actName].act.emplace_back(CheckList());
			_moduleMap[actName].act.emplace_back(CheckKey());
			_moduleMap[actName].act.emplace_back(Colision());
			_moduleMap[actName].runAction = MoveLR();
		}
		if (actName == "落下")
		{
			_moduleMap.emplace(actName, std::move(module));
			_moduleMap[actName].act.emplace_back(CheckList());
			_moduleMap[actName].act.emplace_back(Colision());
			_moduleMap[actName].runAction = Fall();
		}
		if (actName == "落下中")
		{
			_moduleMap.emplace(actName, std::move(module));
			_moduleMap[actName].act.emplace_back(CheckList());
			_moduleMap[actName].act.emplace_back(Colision());
			_moduleMap[actName].runAction = Falling();
		}
		if (actName == "ｼﾞｬﾝﾌﾟ")
		{
			_moduleMap.emplace(actName, std::move(module));
			_moduleMap[actName].act.emplace_back(CheckList());
			_moduleMap[actName].act.emplace_back(CheckKey());
			_moduleMap[actName].runAction = Jump();
		}
		if (actName == "ｼﾞｬﾝﾌﾟ中")
		{
			_moduleMap.emplace(actName, std::move(module));
			_moduleMap[actName].act.emplace_back(CheckList());
			_moduleMap[actName].act.emplace_back(Colision());
			_moduleMap[actName].runAction = Jumping();
		}
		if (actName == "右向き" || actName == "左向き")
		{
			_moduleMap.emplace(actName, std::move(module));
			_moduleMap[actName].act.emplace_back(CheckList());
			_moduleMap[actName].act.emplace_back(CheckKey());
			_moduleMap[actName].runAction = ChangeLR();
		}
		if (actName == "ｼｮｯﾄ")
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
