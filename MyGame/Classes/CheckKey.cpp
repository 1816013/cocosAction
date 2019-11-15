#include "CheckKey.h"

USING_NS_CC;

bool CheckKey::operator()(cocos2d::Sprite & sp, actModule & module)
{
	bool startF = false;
	OPRT_state* input = new OPRT_key(&sp);
	if (input->GetInput(module.keyMode).first)
	{
		startF = true;
	}

	if (input->GetInput(module.keyMode).second == module.keyCode)
	{
		return true;
	}
		
	return false;
}
