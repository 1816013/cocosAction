#include "Fall.h"
#include <Unit/Player.h>
//#include "_debug/_DebugConOut.h"

bool Fall::operator()(cocos2d::Sprite & sp, actModule & module)
{
	auto jumpSpeed = ((Player&)sp).JumpSpeed();
	if (jumpSpeed <= 0)
	{	
		//TRACE("fall\n");
		return true;	
	}
	return false;
}

bool Falling::operator()(cocos2d::Sprite & sp, actModule & module)
{
	auto jumpSpeed = ((Player&)sp).JumpSpeed();
	if (jumpSpeed > 0)
	{
		return false;
	}
	sp.setPositionY(sp.getPositionY() + jumpSpeed);
	jumpSpeed--;
	((Player&)sp).JumpSpeed(jumpSpeed);
	//TRACE("falling\n");
	return true;
}
