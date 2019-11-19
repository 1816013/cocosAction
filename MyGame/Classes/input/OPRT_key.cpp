#include "OPRT_key.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include "_debug/_DebugConOut.h"
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

OPRT_key::OPRT_key(Node* sp)
{
	cocos2d::EventKeyboard::KeyCode dirTbl[static_cast<int>(DIR::MAX)] =
	{
		cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW,
		cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW,
		cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW,
		cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW
	};

	for (auto dir : DIR())
	{
		_keyData[static_cast<int>(TRG_STATE::INPUT)].emplace(dirTbl[static_cast<int>(dir)], false);
	};
	
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)->bool
	{
		if (_keyData[static_cast<int>(TRG_STATE::INPUT)].find(keyCode) != _keyData[static_cast<int>(TRG_STATE::INPUT)].end())
		{
			_keyData[static_cast<int>(TRG_STATE::INPUT)][keyCode] = true;
		}
		//_keyData[static_cast<int>(TRG_STATE::INPUT)].second = keyCode;

		/*if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			_keyData[static_cast<int>(TRG_STATE::INPUT)][static_cast<int>(DIR::UP)] = true;
		}
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW )
		{
			_keyData[static_cast<int>(TRG_STATE::INPUT)][static_cast<int>(DIR::RIGHT)] = true;
		}
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			_keyData[static_cast<int>(TRG_STATE::INPUT)][static_cast<int>(DIR::DOWN)] = true;
		}
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			_keyData[static_cast<int>(TRG_STATE::INPUT)][static_cast<int>(DIR::LEFT)] = true;
		}*/
		return true;
	};

	listener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)->bool
	{
		if (_keyData[static_cast<int>(TRG_STATE::INPUT)].find(keyCode) != _keyData[static_cast<int>(TRG_STATE::INPUT)].end())
		{
			_keyData[static_cast<int>(TRG_STATE::INPUT)][keyCode] = false;
		}
		/*if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			_keyData[static_cast<int>(TRG_STATE::INPUT)][static_cast<int>(DIR::UP)] = false;
		}
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			_keyData[static_cast<int>(TRG_STATE::INPUT)][static_cast<int>(DIR::RIGHT)] = false;
		}
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			_keyData[static_cast<int>(TRG_STATE::INPUT)][static_cast<int>(DIR::DOWN)] = false;
		}
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			_keyData[static_cast<int>(TRG_STATE::INPUT)][static_cast<int>(DIR::LEFT)]= false;
		}*/

		return true;
	};
	sp->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sp);
}


OPRT_TYPE OPRT_key::GetType(void)
{
	return OPRT_TYPE::KEY;
}

