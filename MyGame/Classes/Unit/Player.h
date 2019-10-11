#pragma once
#include "Obj.h"
#include "input/OPRT_state.h"

#define intCast(tag) static_cast<int>(tag)
enum class Tag
{
	ANIM,		// ±ÆÒ°¼®İ
	ACT,		// ±¸¼®İ(1ÌÚ°Ñ–ˆ‚É“®‚©‚·‚à‚Ì)
	TRG_ACT		// ±¸¼®İ(‚»‚Ì‚¾‚¯“®‚©‚·‚à‚Ì)
};

class Player : public Sprite
{
public:
	static cocos2d::Sprite* createSprite();
	Player();
	~Player();
	bool init()override;				// ‰Šú‰»@½Ìß×²Äì¬‚È‚Ç
	void update(float delta)override;		// ½Ìß×²Ä‚ÌˆÚ“®‚È‚Ç
	CREATE_FUNC(Player);
private:
	bool LRflag;
	bool oldLRflag = false;
	bool jumpFlag;
	bool jumpTimeFlag = false;
	int jumpTime = 0;	// ¼Ş¬İÌß’†‚ÌŠÔ

	bool old = false;
	std::unique_ptr<OPRT_state>_inputState;
	Animation* oldanim;

	bool AnimCreate(std::string key, int cnt, float time);
};

