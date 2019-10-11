#pragma once
#include "Obj.h"
#include "input/OPRT_state.h"

#define intCast(tag) static_cast<int>(tag)
enum class Tag
{
	ANIM,		// ｱﾆﾒｰｼｮﾝ
	ACT,		// ｱｸｼｮﾝ(1ﾌﾚｰﾑ毎に動かすもの)
	TRG_ACT		// ｱｸｼｮﾝ(その時だけ動かすもの)
};

class Player : public Sprite
{
public:
	static cocos2d::Sprite* createSprite();
	Player();
	~Player();
	bool init()override;				// 初期化　ｽﾌﾟﾗｲﾄ作成など
	void update(float delta)override;		// ｽﾌﾟﾗｲﾄの移動など
	CREATE_FUNC(Player);
private:
	bool LRflag;
	bool oldLRflag = false;
	bool jumpFlag;
	bool jumpTimeFlag = false;
	int jumpTime = 0;	// ｼﾞｬﾝﾌﾟ中の時間

	bool old = false;
	std::unique_ptr<OPRT_state>_inputState;
	Animation* oldanim;

	bool AnimCreate(std::string key, int cnt, float time);
};

