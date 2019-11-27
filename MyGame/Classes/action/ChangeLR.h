#pragma once
#include <cocos2d.h>
#include "ActionMng.h"

struct ChangeLR
{
	bool operator()(cocos2d::Sprite& sp, actModule& module);
};

