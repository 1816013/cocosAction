#include "MoveLR.h"

bool MoveLR::operator()(cocos2d::Sprite& sp, actModule& module)
{
	sp.setPositionX(sp.getPositionX() + module.speed.x);
	return true;
}
