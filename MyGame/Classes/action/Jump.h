#pragma once
#include <cocos2d.h>
#include "ActionMng.h"


struct Jump
{
	// ¼Þ¬ÝÌßŠJŽn
	bool operator()(cocos2d::Sprite& sp, actModule& module);
}; 

struct Jumping
{	
	// ¼Þ¬ÝÌß’†
	bool operator()(cocos2d::Sprite& sp, actModule& module);
};

