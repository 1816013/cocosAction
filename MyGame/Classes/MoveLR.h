#pragma once
#include <cocos2d.h>
#include <ActionMng.h>

struct actModule;

struct MoveLR
{
	bool operator()(cocos2d::Sprite & sp, actModule&);
};

