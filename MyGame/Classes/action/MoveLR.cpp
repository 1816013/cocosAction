#include "MoveLR.h"
#include "EffectMng.h"
//#include "_debug/_DebugConOut.h"

bool MoveLR::operator()(cocos2d::Sprite& sp, actModule& module)
{
	sp.setPositionX(sp.getPositionX() + module.speed.x);
	//TRACE("moveLR\n");
	return true;
}
