#pragma once
#include "cocos2d.h"

struct Colision
{
	// 当たり判定(関数ｵﾌﾞｼﾞｪｸﾄ)
	bool operator()(cocos2d::Sprite & sp, cocos2d::Vec2 distance) const;	
};