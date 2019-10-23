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


enum class ConerPos
{
	LEFT_UP,
	RIGHT_UP,
	LEFT_DOWN,
	RIGHT_DOWN,
	MAX
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
	Vec2 _pos;
	bool LRflag;					// 左右確認用　右:false 左:true
	bool oldLRflag = false;			// 1ﾌﾚｰﾑ前に右と左どちらを向いていたか
	bool jumpFlag;					// ｼﾞｬﾝﾌﾟﾎﾞﾀﾝが押されたか@削除予定
	bool jumpFancFlag = false;		// ｼﾞｬﾝﾌﾟ中:true	ｼﾞｬﾝﾌﾟしていない時:false

	Size tileSize;// ﾀｲﾙの大きさ
	Size mapTile;// ﾏｯﾌﾟのﾀｲﾙ数一つ目はx, 二つ目はy

	//std::vector<int>colGID;
	std::array<Vec2, static_cast<int>(ConerPos::MAX)>_cPos;
	std::unique_ptr<OPRT_state>_inputState;
	Animation* oldanim;

	int hitc = 0;

	//std::unique_ptr<Colision>col;
	Colision col;
	//bool Colision(const Vec2 ID, TMXLayer & col);
	//bool AnimCreate(std::string key, int cnt, float time);
};

