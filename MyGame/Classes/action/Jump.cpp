#include "Jump.h"
#include "Unit/Player.h"

bool Jump::operator()(cocos2d::Sprite & sp, actModule & module)
{
	auto jumpSpeed = ((Player&)sp).JumpSpeed();
	/*if (jumpSpeed > 0)
	{
		return false;
	}*/
	((Player&)sp).JumpSpeed(20.0f);
	return true;
}

bool Jumping::operator()(cocos2d::Sprite & sp, actModule & module)
{
	auto jumpSpeed = ((Player&)sp).JumpSpeed();
	if (jumpSpeed <= 0)
	{
		return false;
	}
	sp.setPositionY(sp.getPositionY() + jumpSpeed);
	jumpSpeed--;
	((Player&)sp).JumpSpeed(jumpSpeed);
	return true;
}
