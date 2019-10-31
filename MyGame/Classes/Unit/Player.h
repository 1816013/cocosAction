#pragma once
//#include "Obj.h"
#include <input/OPRT_state.h>
#include <array>

enum class Act
{
	run,
	jump,
	idle
};

using DIRArrayPair = std::array<std::pair<Size, Size>, static_cast<int>(DIR::MAX)>;

class Player : public Sprite
{
public:
	// 関数
	static cocos2d::Sprite* createSprite();
	Player();
	~Player();

	bool init()override;				// 初期化　ｽﾌﾟﾗｲﾄ作成
	void update(float delta)override;	// ﾌﾟﾚｲﾔｰの移動とｱﾆﾒｰｼｮﾝ処理
	void MoveLR(Sprite& sp, DIR dir);	// ﾌﾟﾚｲﾔｰの左右移動
	void Jump(Sprite& sp, DIR dir);

	CREATE_FUNC(Player);

	// 変数
	std::array<Vec2, static_cast<int>(DIR::MAX)>SpeedTbl;	// ｽﾋﾟｰﾄﾞ格納用ﾃｰﾌﾞﾙ
	DIRArrayPair _offsetTbl;								// 当たり判定用ｵﾌｾｯﾄﾃｰﾌﾞﾙ
private:
	// 関数
	Animation* SetAnim(DIR dir);	// 方向に応じたｱﾆﾒｰｼｮﾝの設定

	// 変数
	Vec2 _pos;				// ﾌﾟﾚｲﾔｰの座標	
	Size _size;				// ﾌﾟﾚｲﾔｰの大きさ

	bool _LRflag;			// 左右確認用　右:false 左:true
	bool _jumpFancFlag;		// ｼﾞｬﾝﾌﾟ中:true	ｼﾞｬﾝﾌﾟしていない時:false

	int repeatNum;

	std::unique_ptr<OPRT_state>_inputState;
};

