#include "OPRT_touch.h"

OPRT_touch::OPRT_touch(Node* sp)
{
	for (auto itr : DIR())
	{
		data[static_cast<int>(itr)] = false;
	}

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
									if (start_p + Vec2{ margin, margin } > pos && start_p - Vec2{ margin, margin } < pos)
									{
										data[static_cast<int>(DIR::RIGHT)] = false;
										data[static_cast<int>(DIR::LEFT)] = false;
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

void OPRT_touch::Update()
{
	
}

OPRT_TYPE OPRT_touch::GetType(void)
{
	return OPRT_TYPE::TOUCH;
}
