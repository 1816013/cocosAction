#pragma once
#include "cocos2d.h"
#include <input/OPRT_state.h>

// �����ݎg�p���Ă��Ȃ�
class Obj : public cocos2d::Scene
{
public:
	Obj();
	virtual ~Obj();
	virtual void Init(void) = 0;	// �������@���ײč쐬�Ȃ�
	
protected:
	cocos2d::Vec2 _pos;						// ���W				
	cocos2d::Vec2 _size;						// �傫��
};

