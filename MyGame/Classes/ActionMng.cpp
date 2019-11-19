#include "ActionMng.h"



ActionMng::ActionMng()
{
}


ActionMng::~ActionMng()
{
}

void ActionMng::AddActModule(const std::string & actName, actModule & module)
{
	if (actName == "¶ˆÚ“®" || actName == "‰EˆÚ“®")
	{
		_moduleMap.try_emplace(actName, std::move(module));
		_moduleMap[actName].act.emplace_back(CheckKey());
		_moduleMap[actName].act.emplace_back(Colision());
		_moduleMap[actName].runAction = MoveLR();
	}
}

void ActionMng::update(cocos2d::Sprite& sp)
{
	auto check = [this](Sprite& sp, actModule& module)
	{
		int count = 0;
		for (auto listModule = module.act.begin(); listModule == module.act.end(); ++listModule)
		{
			if ((*listModule)(sp, module))
			{	
				count++;
			}		
		}
		if (count >= module.act.size())
		{
			return true;
		}
		return false;
	};

	for (auto mapModule : _moduleMap)
	{
		if (check(sp, mapModule.second))
		{
			mapModule.second.runAction(sp, mapModule.second);
		}
	}
}
