#pragma once
#include "cocos2d.h"
#include "ActionMng.h"

struct actModule;

struct Colision
{
	// 当たり判定(関数ｵﾌﾞｼﾞｪｸﾄ)
	bool operator()(cocos2d::Sprite & sp, actModule& module) const;	
};