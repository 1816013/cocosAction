#pragma once
#include "cocos2d.h"

USING_NS_CC;

struct Colision
{
	bool operator()(Sprite & sp, TMXTiledMap & map, Size distance) const;	// 当たり判定(関数ｵﾌﾞｼﾞｪｸﾄ)
};