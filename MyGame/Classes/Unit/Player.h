#pragma once
//#include "Obj.h"
#include <input/OPRT_state.h>


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
	Vec2 _pos;				// ��ڲ԰�̍��W	
	Size _size;				// ��ڲ԰�̑傫��

	bool _LRflag;			// ���E�m�F�p�@�E:false ��:true
	bool _oldLRflag;		// 1�ڰёO�ɉE�ƍ��ǂ���������Ă�����
	bool _jumpFlag;			// �ެ������݂������ꂽ��@�폜�\��
	bool _jumpFancFlag;		// �ެ��ߒ�:true	�ެ��߂��Ă��Ȃ���:false

	Animation* _oldanim;	// �O��̱�Ұ���@�ړ��\��

	std::unique_ptr<OPRT_state>_inputState;
};

