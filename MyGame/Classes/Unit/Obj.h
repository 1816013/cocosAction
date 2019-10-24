#pragma once
#include "cocos2d.h"
#include <input/OPRT_state.h>

USING_NS_CC;

// ※現在使用していない
class Obj : public Scene
{
public:
	Obj();
	virtual ~Obj();
	virtual void Init(void) = 0;	// 初期化　ｽﾌﾟﾗｲﾄ作成など
	
protected:
	Vec2 _pos;						// 座標				
	Vec2 _size;						// 大きさ
};

