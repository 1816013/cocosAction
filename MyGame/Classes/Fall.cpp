#include "Fall.h"
#include <Unit/Player.h>

bool Fall::operator()(cocos2d::Sprite & sp, actModule & module)
{
	auto jumpSpeed = ((Player&)sp).JumpSpeed();
	if (jumpSpeed > 0)
	{
		return false;
	}
	sp.setPositionY(sp.getPositionY() + jumpSpeed);
	jumpSpeed--;
	((Player&)sp).JumpSpeed(jumpSpeed);
	return true;
}

bool Falling::operator()(cocos2d::Sprite & sp, actModule & module)
{
	//((Player&)sp)._jumpSpeed = 0;
	return true;
}
