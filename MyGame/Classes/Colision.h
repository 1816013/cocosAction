#pragma once
#include "cocos2d.h"

struct Colision
{
	// �����蔻��(�֐���޼ު��)
	bool operator()(cocos2d::Sprite & sp, cocos2d::TMXTiledMap & map, cocos2d::Size distance) const;	
};