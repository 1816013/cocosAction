#pragma once
#include "Obj.h"
#include "input/OPRT_state.h"
#include <vector>
#include <array>
#include <Colision.h>

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
	bool LRflag;						// 左右確認用　右:false 左:true
	bool oldLRflag = false;				// 1ﾌﾚｰﾑ前に右と左どちらを向いていたか
	bool jumpFlag;						// ｼﾞｬﾝﾌﾟﾎﾞﾀﾝが押されたか@削除予定
	bool jumpFancFlag = false;			// ｼﾞｬﾝﾌﾟ中:true	ｼﾞｬﾝﾌﾟしていない時:false

	Size tileSize;						// ﾀｲﾙの大きさ
	Size mapTile;						// ﾏｯﾌﾟのﾀｲﾙ数一つ目はx, 二つ目はy

	std::unique_ptr<OPRT_state>_inputState;
	Animation* oldanim;

	int hitc = 0;

	Colision col;
};

