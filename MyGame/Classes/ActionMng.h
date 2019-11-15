#pragma once
#include <cocos2d.h>
#include <map>
#include <functional>
#include <input/OPRT_state.h>
#include <MoveLR.h>
#include <CheckKey.h>

enum class eAct
{
	run,
	jump,
	fall,
	idle
};

//struct actModule;
using funcActModule = std::function<bool(cocos2d::Sprite&, actModule&)>;
struct actModule
{
	eAct actID;
	std::list<eAct>white;
	std::list<eAct>black;
	std::list<funcActModule>act;
	funcActModule runAction;
	cocos2d::Vec2 speed;
	std::array<cocos2d::Size, 2> colSize;
	TRG_STATE keyMode;
	cocos2d::EventKeyboard::KeyCode keyCode;
};

class ActionMng
{
public:
	ActionMng();
	~ActionMng();
	void SetActModule(void);
	void AddActModule(const std::string& actName, actModule& module);
	void update();


	std::map<std::string, actModule>_moduleMap;
};

//class ActionCtl()
//{
//	Set	// player
//		Add
//		Update
//}