#include "OPRT_key.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include "_debug/_DebugConOut.h"
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

USING_NS_CC;

OPRT_key::OPRT_key(Node* sp)
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)->bool
	{
		if (_keyData[static_cast<int>(TRG_STATE::INPUT)].find(keyCode) != _keyData[static_cast<int>(TRG_STATE::INPUT)].end())
		{
			_keyData[static_cast<int>(TRG_STATE::INPUT)][keyCode] = true;
		}
		return true;
	};

	listener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)->bool
	{
		if (_keyData[static_cast<int>(TRG_STATE::INPUT)].find(keyCode) != _keyData[static_cast<int>(TRG_STATE::INPUT)].end())
		{
			_keyData[static_cast<int>(TRG_STATE::INPUT)][keyCode] = false;
		}
		return true;
	};
	sp->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sp);
}


OPRT_TYPE OPRT_key::GetType(void)
{
	return OPRT_TYPE::KEY;
}

