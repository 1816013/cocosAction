#pragma once
#include <cocos2d.h>
#include "ActionMng.h"

struct Fall
{
	bool operator()(cocos2d::Sprite& sp, actModule& module);
};

struct Falling
{
	bool operator()(cocos2d::Sprite& sp, actModule& module);
};

