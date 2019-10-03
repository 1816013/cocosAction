#include "OPRT_touch.h"

void OPRT_touch::Update(Node* sp)
{
	//data[static_cast<int>(DIR::RIGHT)] = true;
	auto listener = EventListenerTouchOneByOne::create();
	//auto listener = EventListenerMouse::create();
	//auto sprite = Sprite::create("CloseSelected.png");
	listener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		Point pos = touch->getLocation();
		_startTPos = pos;		
		return true;
	};
	listener->onTouchMoved = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		int margin = 50;
		Point pos = touch->getLocation();
		auto start_p = _startTPos;
		if (pos.x > start_p.x + margin)
		{
			data[static_cast<int>(DIR::RIGHT)] = true;
			if (data[static_cast<int>(DIR::LEFT)])
			{
				data[static_cast<int>(DIR::LEFT)] = false;
			}
		}
		if (pos.x < start_p.x - margin)
		{
			data[static_cast<int>(DIR::LEFT)] = true;
			if (data[static_cast<int>(DIR::RIGHT)])
			{
				data[static_cast<int>(DIR::RIGHT)] = false;
			}
		}
		if (pos.y > start_p.y + margin)
		{
			data[static_cast<int>(DIR::UP)] = true;
			if (data[static_cast<int>(DIR::DOWN)])
			{
				data[static_cast<int>(DIR::DOWN)] = false;
			}
		}
		if (pos.y < start_p.y - margin)
		{
			data[static_cast<int>(DIR::DOWN)] = true;
			if (data[static_cast<int>(DIR::UP)])
			{
				data[static_cast<int>(DIR::UP)] = false;
			}
		}
		if (start_p.x + 20 > pos.x && start_p.x - 20 < pos.x)
		{
			data[static_cast<int>(DIR::RIGHT)] = false;
			data[static_cast<int>(DIR::LEFT)] = false;
		}
		if (start_p.y + 20 > pos.y && start_p.y - 20 < pos.y)
		{
			data[static_cast<int>(DIR::UP)] = false;
			data[static_cast<int>(DIR::DOWN)] = false;
		}


		return true;
	};
	listener->onTouchEnded = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		for (int i = 0; i < static_cast<int>(DIR::MAX); i++)
		{
			data[i] = false;
		}
		_startTPos = { -9999, -9999 };
		return true;
	};

	sp->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sp);
}

OPRT_TYPE OPRT_touch::GetType(void)
{
	return OPRT_TYPE::TOUCH;
}

bool OPRT_touch::TouchStart(EventListenerTouchOneByOne* listener)
{
	
	
	return true;
}

void OPRT_touch::TouchEnd(void)
{
}

void OPRT_touch::TouchMove(void)
{
}
