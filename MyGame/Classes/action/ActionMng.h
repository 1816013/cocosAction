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
	CHANGE_LEFT,
	SHOT
};

struct actModule;
using funcActModule = std::function<bool(cocos2d::Sprite&, actModule&)>;

struct actModule
{
	ACT_STATE actID;							// ±¸¼®İID
	std::list<ACT_STATE>white;					// ÎÜ²ÄØ½Ä
	std::list<ACT_STATE>black;					// ÌŞ×¯¸Ø½Ä
	std::list<funcActModule>act;				// Áª¯¸Œn‚Ì±¸¼®İ
	funcActModule runAction;					// Às‚·‚é±¸¼®İ	
	cocos2d::Vec2 speed;						// ˆÚ“®‘¬“x
	std::array<cocos2d::Size, 2> colSize;		// “–‚½‚è”»’è‚Ì»²½Ş
	TRG_STATE keyMode;							// “ü—Í‚ÌÀ²Ìß@ Á‚·‚©‚à
	Timing keyTiming;							// ·°‚ÌÀ²Ğİ¸Ş
	INPUT_ID inputID;							// ·°‚Ìí—Ş
};

class ActionMng
{
public:
	ActionMng();
	//ActionMng(cocos2d::Sprite& sp);
	~ActionMng();
	void AddActModule(const std::string& actName, actModule& module);	// ±¸¼®İ‚Ì¾¯Ä
	void update(cocos2d::Sprite& sp);

	std::map<std::string, actModule>_moduleMap;

	// •Ï”
	ACT_STATE nowAct;	// Œ»İ‚Ì±¸¼®İ
};

