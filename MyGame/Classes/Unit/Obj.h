#pragma once
#include "cocos2d.h"
#include <input/OPRT_state.h>

USING_NS_CC;

class Obj : public Scene
{
public:
	Obj();
	virtual ~Obj();
	virtual void Init(void) = 0;			// �������@���ײč쐬�Ȃ�
	virtual void Update(bool dir) = 0;		// ���ײĂ̈ړ��Ȃ�
	
protected:
	Vec2 _pos;
	Vec2 _size;
};

