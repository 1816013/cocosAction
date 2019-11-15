#include "MoveLR.h"

bool MoveLR::operator()(cocos2d::Sprite& sp, actModule& module)
{
	if (!Colision()(sp, module.speed + module.colSize[0])
		|| !Colision()(sp, module.speed + module.colSize[1]))
	{
		return false;
	}
	sp.setPositionX(sp.getPositionX() + module.speed.x);
	return true;
}
