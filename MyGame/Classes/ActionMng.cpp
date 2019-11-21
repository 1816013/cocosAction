#include "ActionMng.h"

USING_NS_CC;

ActionMng::ActionMng()
{
}


ActionMng::~ActionMng()
{
}

void ActionMng::AddActModule(const std::string & actName, actModule & module)
{
	if (actName == "左移動" || actName == "右移動")
	{
		_moduleMap.try_emplace(actName, std::move(module));
		_moduleMap[actName].act.emplace_back(CheckKey());
		_moduleMap[actName].act.emplace_back(Colision());
		_moduleMap[actName].runAction = MoveLR();
	}
	if (actName == "ｼﾞｬﾝﾌﾟ")
	{
		_moduleMap.try_emplace(actName, std::move(module));
		_moduleMap[actName].act.emplace_back(CheckKey());
		_moduleMap[actName].runAction = Jump();
	}
	if (actName == "ｼﾞｬﾝﾌﾟ中")
	{
		_moduleMap.try_emplace(actName, std::move(module));
		_moduleMap[actName].act.emplace_back(Colision());
		_moduleMap[actName].runAction = Jumping();
	}
	if (actName == "落下")
	{
		_moduleMap.try_emplace(actName, std::move(module));
		_moduleMap[actName].act.emplace_back(Colision());
		_moduleMap[actName].runAction = Fall();
	}
	/*if (actName == "落下中")
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
