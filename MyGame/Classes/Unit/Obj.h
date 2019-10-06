#pragma once
#include "cocos2d.h"
#include <input/OPRT_state.h>

USING_NS_CC;

class Obj : public Scene
{
public:
	Obj();
	virtual ~Obj();
	virtual void Init(void) = 0;			// ‰Šú‰»@½Ìß×²Äì¬‚È‚Ç
	virtual void Update(bool dir) = 0;		// ½Ìß×²Ä‚ÌˆÚ“®‚È‚Ç
	
protected:
	Vec2 _pos;
	Vec2 _size;
};

