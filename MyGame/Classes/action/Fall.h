#pragma once
#include <cocos2d.h>
#include "ActionMng.h"

struct Fall
{
	// —Ž‰ºŠJŽn
	bool operator()(cocos2d::Sprite& sp, actModule& module);
};

struct Falling
{
	// —Ž‰º’†
	bool operator()(cocos2d::Sprite& sp, actModule& module);
};

