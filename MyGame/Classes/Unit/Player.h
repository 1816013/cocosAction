#pragma once
//#include "Obj.h"
#include <input/OPRT_state.h>
#include <array>

using DIRArrayPair = std::array<std::pair<Size, Size>, static_cast<int>(DIR::MAX)>;

class Player : public Sprite
{
public:
	static cocos2d::Sprite* createSprite();
	Player();
	~Player();

	bool init()override;				// 初期化　ｽﾌﾟﾗｲﾄ作成
	void update(float delta)override;	// ﾌﾟﾚｲﾔｰの移動とｱﾆﾒｰｼｮﾝ処理
	void MoveLR(Sprite& sp, DIR dir);
	DIR GetDIR(void);

	std::array<Vec2, static_cast<int>(DIR::MAX)>SpeedTbl;
	DIRArrayPair _offsetTbl;
	DIR _dir;

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

