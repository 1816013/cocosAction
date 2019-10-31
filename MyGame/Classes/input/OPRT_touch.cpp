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
										data[static_cast<int>(DIR::RIGHT)].first = true;
										if (data[static_cast<int>(DIR::LEFT)].first)
										{
											data[static_cast<int>(DIR::LEFT)].first = false;
										}
									}
									if (pos.x < start_p.x - margin)
									{
										data[static_cast<int>(DIR::LEFT)].first = true;
										if (data[static_cast<int>(DIR::RIGHT)].first)
										{
											data[static_cast<int>(DIR::RIGHT)].first = false;
										}
									}
									if (pos.y > start_p.y + margin)
									{
										data[static_cast<int>(DIR::UP)].first = true;
										if (data[static_cast<int>(DIR::DOWN)].first)
										{
											data[static_cast<int>(DIR::DOWN)].first = false;
										}
									}
									if (pos.y < start_p.y - margin)
									{
										data[static_cast<int>(DIR::DOWN)].first = true;
										if (data[static_cast<int>(DIR::UP)].first)
										{
											data[static_cast<int>(DIR::UP)].first = false;
										}
									}
									if (start_p + Vec2{ margin, margin } > pos && start_p - Vec2{ margin, margin } < pos)
									{
										for (auto itr : DIR())
										{
											data[static_cast<int>(itr)].first = false;
										}
									}
									return true;
								};
	listener->onTouchEnded = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
								{
									for (auto itr : DIR())
									{
										data[static_cast<int>(itr)].first = false;
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
