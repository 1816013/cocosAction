#include "OPRT_key.h"
#include "_debug/_DebugConOut.h"

OPRT_key::OPRT_key(Node* sp)
{
	for (auto itr : DIR())
	{
		data[static_cast<int>(itr)] = false;
	}

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)->bool
								{
									if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
									{
										data[static_cast<int>(DIR::UP)] = true;
									}
									if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW )
									{
										data[static_cast<int>(DIR::RIGHT)] = true;
									}
									if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
									{
										data[static_cast<int>(DIR::DOWN)] = true;
									}
									if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
									{
										data[static_cast<int>(DIR::LEFT)] = true;
									}
									return true;
								};

	listener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)->bool
								{
									if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
									{
										data[static_cast<int>(DIR::UP)] = false;
									}
									if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
									{
										data[static_cast<int>(DIR::RIGHT)] = false;
									}
									if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
									{
										data[static_cast<int>(DIR::DOWN)] = false;
									}
									if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
									{
										data[static_cast<int>(DIR::LEFT)] = false;
									}
									return true;
								};
	sp->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sp);
}

void OPRT_key::Update()
{
	for (auto itr : DIR())
	{
		data[static_cast<int>(itr)] = false;
	}
}

OPRT_TYPE OPRT_key::GetType(void)
{
	return OPRT_TYPE::KEY;
}
