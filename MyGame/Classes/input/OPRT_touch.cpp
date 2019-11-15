#include "OPRT_touch.h"

OPRT_touch::OPRT_touch(Node* sp)
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		Point pos = touch->getLocation();
		_startTPos = pos;
		return true;
	};
	listener->onTouchMoved = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		float margin = 30.0f;
		Point pos = touch->getLocation();
		auto start_p = _startTPos;
		if (pos.x > start_p.x + margin)
		{
			_touchData[static_cast<int>(TRG_STATE::INPUT)][static_cast<int>(DIR::RIGHT)] = true;
			if (_touchData[static_cast<int>(TRG_STATE::INPUT)][static_cast<int>(DIR::LEFT)])
			{
				_touchData[static_cast<int>(TRG_STATE::INPUT)][static_cast<int>(DIR::LEFT)] = false;
			}
		}
		if (pos.x < start_p.x - margin)
		{
			_touchData[static_cast<int>(TRG_STATE::INPUT)][static_cast<int>(DIR::LEFT)] = true;
			if (_touchData[static_cast<int>(TRG_STATE::INPUT)][static_cast<int>(DIR::RIGHT)])
			{
				_touchData[static_cast<int>(TRG_STATE::INPUT)][static_cast<int>(DIR::RIGHT)] = false;
			}
		}
		if (pos.y > start_p.y + margin)
		{
			_touchData[static_cast<int>(TRG_STATE::INPUT)][static_cast<int>(DIR::UP)] = true;
			if (_touchData[static_cast<int>(TRG_STATE::INPUT)][static_cast<int>(DIR::DOWN)])
			{
				_touchData[static_cast<int>(TRG_STATE::INPUT)][static_cast<int>(DIR::DOWN)] = false;
			}
		}
		if (pos.y < start_p.y - margin)
		{
			_touchData[static_cast<int>(TRG_STATE::INPUT)][static_cast<int>(DIR::DOWN)] = true;
			if (_touchData[static_cast<int>(TRG_STATE::INPUT)][static_cast<int>(DIR::UP)])
			{
				_touchData[static_cast<int>(TRG_STATE::INPUT)][static_cast<int>(DIR::UP)] = false;
			}
		}
		if (start_p + Vec2{ margin, margin } > pos && start_p - Vec2{ margin, margin } < pos)
		{
			for (auto itr : DIR())
			{
				_touchData[static_cast<int>(TRG_STATE::INPUT)][static_cast<int>(itr)] = false;
			}
		}
		return true;
	};
	listener->onTouchEnded = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		for (auto itr : DIR())
		{
			_touchData[static_cast<int>(TRG_STATE::INPUT)][static_cast<int>(itr)] = false;
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
