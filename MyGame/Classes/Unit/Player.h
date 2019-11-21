#pragma once
//#include "Obj.h"
#include <array>
#include <input/OPRT_state.h>
#include <ActionMng.h>

using DIRArrayPair = std::array<std::pair<cocos2d::Size, cocos2d::Size>, static_cast<int>(DIR::MAX)>;

class Player : public cocos2d::Sprite
{
public:
	// 関数
	static cocos2d::Sprite* createSprite();
	Player();
	~Player();

	bool init()override;								// 初期化　ｽﾌﾟﾗｲﾄ作成
	void update(float delta)override;					// ﾌﾟﾚｲﾔｰの移動とｱﾆﾒｰｼｮﾝ処理
	void Jump(cocos2d::Sprite& sp, DIR dir);			// ｼﾞｬﾝﾌﾟ
	//void Gravity(Sprite& sp);							// 重力
	void ChangeLR(cocos2d::Sprite& sp, DIR dir);		// 左右切り替え
	void JumpSpeed(float speed);						// ｼﾞｬﾝﾌﾟのｽﾋﾟｰﾄﾞを取得する
	float JumpSpeed(void);								// ｼﾞｬﾝﾌﾟのｽﾋﾟｰﾄﾞをｾｯﾄする
	CREATE_FUNC(Player);
	std::unique_ptr<OPRT_state>_inputState;

	// 変数
	std::shared_ptr<ActionMng>_actMng;
	float _jumpSpeed;
private:
	// 関数
	cocos2d::Animation* SetAnim(DIR dir);	// 方向に応じたｱﾆﾒｰｼｮﾝの設定

	// 変数
	cocos2d::Vec2 _pos;				// ﾌﾟﾚｲﾔｰの座標	
	cocos2d::Size _size;				// ﾌﾟﾚｲﾔｰの大きさ

	//bool _flagLR;			// 左右確認用　右:false 左:true
	bool _jumpFancFlag;		// ｼﾞｬﾝﾌﾟ中:true	ｼﾞｬﾝﾌﾟしていない時:false
	int _repeatNum;


	
};

