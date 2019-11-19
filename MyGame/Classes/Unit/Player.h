#pragma once
//#include "Obj.h"
#include <array>
#include <input/OPRT_state.h>
#include <ActionMng.h>



using DIRArrayPair = std::array<std::pair<Size, Size>, static_cast<int>(DIR::MAX)>;

class Player : public Sprite
{
public:
	// 関数
	static cocos2d::Sprite* createSprite();
	Player();
	~Player();

	bool init()override;					// 初期化　ｽﾌﾟﾗｲﾄ作成
	void update(float delta)override;		// ﾌﾟﾚｲﾔｰの移動とｱﾆﾒｰｼｮﾝ処理
	void Jump(Sprite& sp, DIR dir);			// ｼﾞｬﾝﾌﾟ
	void Gravity(Sprite& sp);				// 重力
	void ChangeLR(Sprite& sp, DIR dir);		// 左右切り替え

	CREATE_FUNC(Player);
	std::unique_ptr<OPRT_state>_inputState;

	// 変数
	std::array<Vec2, static_cast<int>(DIR::MAX)>SpeedTbl;	// ｽﾋﾟｰﾄﾞ格納用ﾃｰﾌﾞﾙ
	DIRArrayPair _offsetTbl;								// 当たり判定用ｵﾌｾｯﾄﾃｰﾌﾞﾙ
	std::shared_ptr<ActionMng>_actMng;
private:
	// 関数
	Animation* SetAnim(DIR dir);	// 方向に応じたｱﾆﾒｰｼｮﾝの設定

	// 変数
	Vec2 _pos;				// ﾌﾟﾚｲﾔｰの座標	
	Size _size;				// ﾌﾟﾚｲﾔｰの大きさ

	//bool _flagLR;			// 左右確認用　右:false 左:true
	bool _jumpFancFlag;		// ｼﾞｬﾝﾌﾟ中:true	ｼﾞｬﾝﾌﾟしていない時:false
	int _repeatNum;

	
	// test
	Vec2 _speed = { 0, 0 };
	std::array<cocos2d::Size, 2>_colSize = { cocos2d::Size(0, 0), cocos2d::Size(0, 0)};

	
};

