#pragma once
#include "Obj.h"
#include "input/OPRT_state.h"

#define intCast(tag) static_cast<int>(tag)
enum class Tag
{
	ANIM,		// ��Ұ���
	ACT,		// �����(1�ڰі��ɓ���������)
	TRG_ACT		// �����(���̎���������������)
};

class Player : public Sprite
{
public:
	static cocos2d::Sprite* createSprite();
	Player();
	~Player();
	bool init()override;				// �������@���ײč쐬�Ȃ�
	void update(float delta)override;		// ���ײĂ̈ړ��Ȃ�
	CREATE_FUNC(Player);
private:
	bool LRflag;
	bool oldLRflag = false;
	bool jumpFlag;
	bool jumpTimeFlag = false;
	int jumpTime = 0;	// �ެ��ߒ��̎���

	bool old = false;
	std::unique_ptr<OPRT_state>_inputState;
	Animation* oldanim;

	bool AnimCreate(std::string key, int cnt, float time);
};

