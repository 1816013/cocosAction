#pragma once
#include <cocos2d.h>
#include "ActionMng.h"

struct Jump
{
	bool operator()(cocos2d::Sprite& sp, actModule& module);
}; 

struct Jumping
{
	bool operator()(cocos2d::Sprite& sp, actModule& module);
};

