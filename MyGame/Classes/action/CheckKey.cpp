#include "CheckKey.h"
#include "Unit/Player.h"

USING_NS_CC;

bool CheckKey::operator()(cocos2d::Sprite & sp, actModule & module)
{
	if (((Player&)sp)._inputState->GetInput(module.keyMode, module.inputID))
	{	
		if (module.keyTiming == Timing::ON)
		{
			return true;
		}
		if (module.keyTiming == Timing::ON_MOM)
		{
			if (((Player&)sp)._inputState->GetInput(module.keyMode, module.inputID) && !((Player&)sp)._inputState->GetInput(TRG_STATE::OLD, module.inputID))
			{
				return true;
			}
		}
	}	
	else
	{
		if (module.keyTiming == Timing::OFF)
		{
			return true;
		}
		if (module.keyTiming == Timing::OFF_MOM)
		{
			if (!((Player&)sp)._inputState->GetInput(module.keyMode, module.inputID) && !((Player&)sp)._inputState->GetInput(TRG_STATE::OLD, module.inputID))
			{
				return true;
			}
		}
	}
	return false;
}
