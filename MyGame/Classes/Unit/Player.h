#pragma once
//#include "Obj.h"
#include <array>
#include "input/OPRT_state.h"
#include "action/ActionMng.h"


using DIRArrayPair = std::array<std::pair<cocos2d::Size, cocos2d::Size>, static_cast<int>(INPUT_ID::MAX)>;

class Player : public cocos2d::Sprite
{
public:
	// 関数
	static cocos2d::Sprite* createSprite();
	Player();
	~Player();

	bool init()override;				// 初期化　ｽﾌﾟﾗｲﾄ作成
	void update(float delta)override;	// ﾌﾟﾚｲﾔｰの移動とｱﾆﾒｰｼｮﾝ処理
	void JumpSpeed(float speed);		// ｼﾞｬﾝﾌﾟのｽﾋﾟｰﾄﾞを取得する
	float JumpSpeed(void);				// ｼﾞｬﾝﾌﾟのｽﾋﾟｰﾄﾞをｾｯﾄする
	void ActState(ACT_STATE state);		// ﾌﾟﾚｲﾔｰの状態をｾｯﾄする				
	ACT_STATE ActState(void);			// ﾌﾟﾚｲﾔｰの状態を取得する

	CREATE_FUNC(Player);
	std::unique_ptr<OPRT_state>_inputState;

	// 変数
	std::shared_ptr<ActionMng>_actMng;
	
private:
	// 関数
	cocos2d::Animation* SetAnim(ACT_STATE state);	// 方向に応じたｱﾆﾒｰｼｮﾝの設定

	// 変数
	cocos2d::Vec2 _pos;				// ﾌﾟﾚｲﾔｰの座標	
	cocos2d::Size _size;				// ﾌﾟﾚｲﾔｰの大きさ

	int _repeatNum;

	float _jumpSpeed;
	ACT_STATE _nowState;

	int count;
};

