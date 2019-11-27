#pragma once
//#include "Obj.h"
#include <array>
#include "input/OPRT_state.h"
#include "action/ActionMng.h"


using DIRArrayPair = std::array<std::pair<cocos2d::Size, cocos2d::Size>, static_cast<int>(DIR::MAX)>;

class Player : public cocos2d::Sprite
{
public:
	// ŠÖ”
	static cocos2d::Sprite* createSprite();
	Player();
	~Player();

	bool init()override;				// ‰Šú‰»@½Ìß×²Äì¬
	void update(float delta)override;	// ÌßÚ²Ô°‚ÌˆÚ“®‚Æ±ÆÒ°¼®İˆ—
	void JumpSpeed(float speed);		// ¼Ş¬İÌß‚Ì½Ëß°ÄŞ‚ğæ“¾‚·‚é
	float JumpSpeed(void);				// ¼Ş¬İÌß‚Ì½Ëß°ÄŞ‚ğ¾¯Ä‚·‚é
	void ActState(ACT_STATE state);		// ÌßÚ²Ô°‚Ìó‘Ô‚ğ¾¯Ä‚·‚é				
	ACT_STATE ActState(void);			// ÌßÚ²Ô°‚Ìó‘Ô‚ğæ“¾‚·‚é

	CREATE_FUNC(Player);
	std::unique_ptr<OPRT_state>_inputState;

	

	// •Ï”
	std::shared_ptr<ActionMng>_actMng;
	
private:
	// ŠÖ”
	cocos2d::Animation* SetAnim(ACT_STATE state);	// •ûŒü‚É‰‚¶‚½±ÆÒ°¼®İ‚Ìİ’è

	// •Ï”
	cocos2d::Vec2 _pos;				// ÌßÚ²Ô°‚ÌÀ•W	
	cocos2d::Size _size;				// ÌßÚ²Ô°‚Ì‘å‚«‚³

	int _repeatNum;

	float _jumpSpeed;
	ACT_STATE _nowState;

	int count;
};

