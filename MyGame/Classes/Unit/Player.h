#pragma once
//#include "Obj.h"
#include <input/OPRT_state.h>


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

	bool init()override;				// 初期化　ｽﾌﾟﾗｲﾄ作成
	void update(float delta)override;	// ﾌﾟﾚｲﾔｰの移動とｱﾆﾒｰｼｮﾝ処理

	CREATE_FUNC(Player);
private:
	Vec2 _pos;				// ﾌﾟﾚｲﾔｰの座標	
	Size _size;				// ﾌﾟﾚｲﾔｰの大きさ

	bool _LRflag;			// 左右確認用　右:false 左:true
	bool _oldLRflag;		// 1ﾌﾚｰﾑ前に右と左どちらを向いていたか
	bool _jumpFlag;			// ｼﾞｬﾝﾌﾟﾎﾞﾀﾝが押されたか@削除予定
	bool _jumpFancFlag;		// ｼﾞｬﾝﾌﾟ中:true	ｼﾞｬﾝﾌﾟしていない時:false

	Animation* _oldanim;	// 前回のｱﾆﾒｰｼｮﾝ@移動予定

	std::unique_ptr<OPRT_state>_inputState;
};

