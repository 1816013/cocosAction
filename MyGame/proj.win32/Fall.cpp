#include "Fall.h"

bool Fall::operator()(cocos2d::Sprite & sp, actModule & module)
{
	sp.setPositionY(sp.getPositionY() + module.speed.y);
	return true;
}
