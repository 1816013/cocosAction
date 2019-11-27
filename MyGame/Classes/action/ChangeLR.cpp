#include "ChangeLR.h"
#include <Unit/Player.h>

bool ChangeLR::operator()(cocos2d::Sprite & sp, actModule & module)
{
	bool flagLR;
	module.actID = ((Player&)sp).ActState();
	if (module.keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		flagLR = false;
	}
	else
	{
		flagLR = true;
	}
	sp.runAction(cocos2d::FlipX::create(flagLR));

	return true;
}
