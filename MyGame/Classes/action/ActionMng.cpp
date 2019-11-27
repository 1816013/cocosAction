#include "ActionMng.h"
#include <Unit/Player.h>
#include "CheckList.h"
#include "CheckKey.h"
#include "Colision.h"
#include "MoveLR.h"
#include "Fall.h"
#include "Jump.h"
#include "ChangeLR.h"

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
		if (actName == "¶ˆÚ“®" || actName == "‰EˆÚ“®")
		{
			_moduleMap.emplace(actName, std::move(module));
			_moduleMap[actName].act.emplace_back(CheckList());
			_moduleMap[actName].act.emplace_back(CheckKey());
			_moduleMap[actName].act.emplace_back(Colision());
			_moduleMap[actName].runAction = MoveLR();
		}
		if (actName == "¼Þ¬ÝÌß")
		{
			_moduleMap.emplace(actName, std::move(module));
			_moduleMap[actName].act.emplace_back(CheckList());
			_moduleMap[actName].act.emplace_back(CheckKey());
			_moduleMap[actName].runAction = Jump();
		}
		if (actName == "¼Þ¬ÝÌß’†")
		{
			_moduleMap.emplace(actName, std::move(module));
			_moduleMap[actName].act.emplace_back(CheckList());
			_moduleMap[actName].act.emplace_back(Colision());
			_moduleMap[actName].runAction = Jumping();
		}
		if (actName == "—Ž‰º")
		{
			_moduleMap.emplace(actName, std::move(module));
			_moduleMap[actName].act.emplace_back(CheckList());
			_moduleMap[actName].act.emplace_back(Colision());
			_moduleMap[actName].runAction = Fall();
		}
		if (actName == "—Ž‰º’†")
		{
			_moduleMap.emplace(actName, std::move(module));
			_moduleMap[actName].act.emplace_back(CheckList());
			_moduleMap[actName].act.emplace_back(Colision());
			_moduleMap[actName].runAction = Falling();
		}
		if (actName == "‰EŒü‚«" || actName == "¶Œü‚«")
		{
			_moduleMap.emplace(actName, std::move(module));
			_moduleMap[actName].act.emplace_back(CheckList());
			_moduleMap[actName].act.emplace_back(CheckKey());
			_moduleMap[actName].runAction = ChangeLR();
		}
	}
	/*if (actName == "—Ž‰º’†")
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

	int count = 0;
	for (auto mapModule : _moduleMap)
	{
		if (check(sp, mapModule.second))
		{
			if (mapModule.second.runAction(sp, mapModule.second))
			{
				((Player&)sp).ActState(mapModule.second.actID);		
			}
			else
			{
				count++;
			}
		}
		else 
		{
			count++;
		}
	}
	if (count >= _moduleMap.size())
	{
		((Player&)sp).ActState(ACT_STATE::IDLE);
	}
	
}
