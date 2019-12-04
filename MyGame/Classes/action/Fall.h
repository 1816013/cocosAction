#pragma once
#include <cocos2d.h>
#include "ActionMng.h"

struct Fall
{
	// 落下開始
	bool operator()(cocos2d::Sprite& sp, actModule& module);
};

struct Falling
{
	// 落下中
	bool operator()(cocos2d::Sprite& sp, actModule& module);
};

