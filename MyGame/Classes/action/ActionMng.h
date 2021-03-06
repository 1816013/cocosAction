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
	ACT_STATE actID;							// ｱｸｼｮﾝID
	std::list<ACT_STATE>white;					// ﾎﾜｲﾄﾘｽﾄ
	std::list<ACT_STATE>black;					// ﾌﾞﾗｯｸﾘｽﾄ
	std::list<funcActModule>act;				// ﾁｪｯｸ系のｱｸｼｮﾝ
	funcActModule runAction;					// 実行するｱｸｼｮﾝ	
	cocos2d::Vec2 speed;						// 移動速度
	std::array<cocos2d::Size, 2> colSize;		// 当たり判定のｻｲｽﾞ
	TRG_STATE keyMode;							// 入力のﾀｲﾌﾟ@ 消すかも
	Timing keyTiming;							// ｷｰのﾀｲﾐﾝｸﾞ
	INPUT_ID inputID;							// ｷｰの種類
};

class ActionMng
{
public:
	ActionMng();
	//ActionMng(cocos2d::Sprite& sp);
	~ActionMng();
	void AddActModule(const std::string& actName, actModule& module);	// ｱｸｼｮﾝのｾｯﾄ
	void update(cocos2d::Sprite& sp);

	std::map<std::string, actModule>_moduleMap;

	// 変数
	ACT_STATE nowAct;	// 現在のｱｸｼｮﾝ
};

