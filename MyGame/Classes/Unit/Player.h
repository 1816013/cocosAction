#pragma once
#include "Obj.h"
#include "input/OPRT_state.h"
#include <vector>
#include <array>
#include <Colision.h>

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
	bool init()override;				// �������@���ײč쐬
	void update(float delta)override;	// ��ڲ԰�̈ړ��Ʊ�Ұ��ݏ���
	CREATE_FUNC(Player);
private:
	bool LRflag;						// ���E�m�F�p�@�E:false ��:true
	bool oldLRflag = false;				// 1�ڰёO�ɉE�ƍ��ǂ���������Ă�����
	bool jumpFlag;						// �ެ������݂������ꂽ��@�폜�\��
	bool jumpFancFlag = false;			// �ެ��ߒ�:true	�ެ��߂��Ă��Ȃ���:false

	Size tileSize;						// ��ق̑傫��
	Size mapTile;						// ϯ�߂���ِ���ڂ�x, ��ڂ�y

	std::unique_ptr<OPRT_state>_inputState;
	Animation* oldanim;

	int hitc = 0;

	Colision col;
};

