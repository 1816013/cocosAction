#pragma once
#include <cocos2d.h>
#include "ActionMng.h"

struct ActModule;

struct CheckList
{
	bool operator()(cocos2d::Sprite& sprite, ActModule& module);
};

