#include "ActionMng.h"
#include <Unit/Player.h>
#include "MoveLR.h"
#include "CheckKey.h"
#include "Colision.h"
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
	if (actName == "���ړ�" || actName == "�E�ړ�")
	{
		_moduleMap.try_emplace(actName, std::move(module));
		_moduleMap[actName].act.emplace_back(CheckKey());
		_moduleMap[actName].act.emplace_back(Colision());
		_moduleMap[actName].runAction = MoveLR();
	}
	if (actName == "�ެ���")
	{
		_moduleMap.try_emplace(actName, std::move(module));
		_moduleMap[actName].act.emplace_back(CheckKey());
		_moduleMap[actName].runAction = Jump();
	}
	if (actName == "�ެ��ߒ�")
	{
		_moduleMap.try_emplace(actName, std::move(module));
		_moduleMap[actName].act.emplace_back(Colision());
		_moduleMap[actName].runAction = Jumping();
	}
	if (actName == "����")
	{
		_moduleMap.try_emplace(actName, std::move(module));
		_moduleMap[actName].act.emplace_back(Colision());
		_moduleMap[actName].runAction = Fall();
	}
	if (actName == "�E����" || actName == "������")
	{
		/*_moduleMap.try_emplace(actName, std::move(module));
		_moduleMap[actName].act.emplace_back(CheckKey());
		_moduleMap[actName].act.emplace_back(Colision());*/
		//_moduleMap[actName].runAction = ChangeLR();
	}
	/*if (actName == "������")
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
			((Player&)sp).ActState(mapModule.second.actID);
			mapModule.second.runAction(sp, mapModule.second);
		}
		else
		{
			((Player&)sp).ActState(ACT_STATE::IDLE);
		}
	}
}
