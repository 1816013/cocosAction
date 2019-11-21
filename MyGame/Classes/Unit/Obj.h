#pragma once
#include "cocos2d.h"
#include <input/OPRT_state.h>

// ※現在使用していない
class Obj : public cocos2d::Scene
{
public:
	Obj();
	virtual ~Obj();
	virtual void Init(void) = 0;	// 初期化　ｽﾌﾟﾗｲﾄ作成など
	
protected:
	cocos2d::Vec2 _pos;						// 座標				
	cocos2d::Vec2 _size;						// 大きさ
};

