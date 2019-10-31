#include "OPRT_key.h"
#include "_debug/_DebugConOut.h"

OPRT_key::OPRT_key(Node* sp)
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)->bool
								{
									if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
									{
										data[static_cast<int>(DIR::UP)].first = true;
										data[static_cast<int>(DIR::UP)].second = TRG_KEY::TRG;
									}
									if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW )
									{
										data[static_cast<int>(DIR::RIGHT)].first = true;
									}
									if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
									{
										data[static_cast<int>(DIR::DOWN)].first = true;
									}
									if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
									{
										data[static_cast<int>(DIR::LEFT)].first = true;
									}
									return true;
								};

	listener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)->bool
								{
									if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
									{
										data[static_cast<int>(DIR::UP)].first = false;
									}
									if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
									{
										data[static_cast<int>(DIR::RIGHT)].first = false;
									}
									if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
									{
										data[static_cast<int>(DIR::DOWN)].first = false;
									}
									if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
									{
										data[static_cast<int>(DIR::LEFT)].first = false;
									}
									return true;
								};
	sp->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sp);
}

void OPRT_key::Update()
{
	for (auto itr : DIR())
	{
		if (data[static_cast<int>(itr)].second == TRG_KEY::TRG)
		{
			data[static_cast<int>(itr)].first = false;
		}
	}
}

OPRT_TYPE OPRT_key::GetType(void)
{
	return OPRT_TYPE::KEY;
}

void OPRT_key::SetTrg(DIR dir, TRG_KEY trg)
{
	data[static_cast<int>(dir)].second = trg;
}
