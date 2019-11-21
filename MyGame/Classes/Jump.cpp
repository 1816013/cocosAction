#include "Jump.h"
#include <Unit/Player.h>

bool Jump::operator()(cocos2d::Sprite & sp, actModule & module)
{
	((Player&)sp)._jumpSpeed = 20.0f;
	return true;
}

bool Jumping::operator()(cocos2d::Sprite & sp, actModule & module)
{
	if (((Player&)sp)._jumpSpeed <= 0)
	{
		return false;
	}
	sp.setPositionY(sp.getPositionY() + ((Player&)sp)._jumpSpeed);
	((Player&)sp)._jumpSpeed--;
	module.speed.y = ((Player&)sp)._jumpSpeed;

	return true;
}
