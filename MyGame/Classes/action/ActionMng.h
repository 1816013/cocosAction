#pragma once
#include <cocos2d.h>
#include <map>
#include <functional>
#include <input/OPRT_state.h>


enum class ACT_STATE
{
	RUN,
	JUMP,
	JUMPING,
	FALL,
	FALLING,
	IDLE,
	CHANGE_RIGHT,
	CHANGE_LEFT
};

struct actModule;
using funcActModule = std::function<bool(cocos2d::Sprite&, actModule&)>;

struct actModule
{
	ACT_STATE actID;
	std::list<ACT_STATE>white;
	std::list<ACT_STATE>black;
	std::list<funcActModule>act;
	funcActModule runAction;
	cocos2d::Vec2 speed;
	std::array<cocos2d::Size, 2> colSize;
	TRG_STATE keyMode;
	Timing keyTiming;
	cocos2d::EventKeyboard::KeyCode keyCode;
};

class ActionMng
{
public:
	ActionMng();
	//ActionMng(cocos2d::Sprite& sp);
	~ActionMng();
	void AddActModule(const std::string& actName, actModule& module);
	void update(cocos2d::Sprite& sp);

	std::map<std::string, actModule>_moduleMap;

	// ïœêî
	ACT_STATE nowAct;	// åªç›ÇÃ±∏ºÆ›
};

