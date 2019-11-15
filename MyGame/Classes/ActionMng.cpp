#include "ActionMng.h"



ActionMng::ActionMng()
{
}


ActionMng::~ActionMng()
{
}

void ActionMng::SetActModule(void)
{
}

void ActionMng::AddActModule(const std::string & actName, actModule & module)
{
	if (actName == "ç∂à⁄ìÆ")
	{
		_moduleMap.try_emplace(actName, std::move(module));
		_moduleMap[actName].act.emplace_back(CheckKey());
		_moduleMap[actName].act.emplace_back(MoveLR());
	}
}

void ActionMng::update()
{
	auto check = [this]()
	{
		for (auto itr : _moduleMap)
		{
			if (itr.second.runAction)
			{
				return false;
			}
		}
		return true;
	};

	for (auto itr : _moduleMap)
	{
		if (check())
		{

		}
	}
}
