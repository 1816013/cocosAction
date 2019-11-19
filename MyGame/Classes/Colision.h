#pragma once
#include "cocos2d.h"
#include "ActionMng.h"

struct actModule;

struct Colision
{
	// “–‚½‚è”»’è(ŠÖ”µÌŞ¼Şª¸Ä)
	bool operator()(cocos2d::Sprite & sp, actModule& module) const;	
};