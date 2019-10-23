#pragma once
#include "cocos2d.h"

USING_NS_CC;

struct Colision
{
	bool operator()(const Vec2 ID, TMXLayer & col, const Size mapTile) const;		
};