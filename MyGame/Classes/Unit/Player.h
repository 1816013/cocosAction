#pragma once
#include "Obj.h"

class Player :
	public Obj
{
public:
	Player();
	~Player();
	void Init(void);					// �������@���ײč쐬�Ȃ�
	void Update(bool dir)override;		// ���ײĂ̈ړ��Ȃ�
private:
	Sprite* sprite;
};

