#pragma once
#include "cocos2d.h"

struct Colision
{
	// “–‚½‚è”»’è(ŠÖ”µÌŞ¼Şª¸Ä)
	bool operator()(cocos2d::Sprite & sp, cocos2d::Vec2 distance) const;	
};