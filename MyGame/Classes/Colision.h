#pragma once
#include "cocos2d.h"

USING_NS_CC;

struct Colision
{
	bool operator()(Sprite & sp, TMXTiledMap & map, Size distance) const;	// �����蔻��(�֐���޼ު��)
};