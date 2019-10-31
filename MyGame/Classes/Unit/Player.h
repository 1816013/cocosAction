#pragma once
//#include "Obj.h"
#include <input/OPRT_state.h>
#include <array>

enum class Act
{
	run,
	jump,
	idle
};

using DIRArrayPair = std::array<std::pair<Size, Size>, static_cast<int>(DIR::MAX)>;

class Player : public Sprite
{
public:
	// �֐�
	static cocos2d::Sprite* createSprite();
	Player();
	~Player();

	bool init()override;				// �������@���ײč쐬
	void update(float delta)override;	// ��ڲ԰�̈ړ��Ʊ�Ұ��ݏ���
	void MoveLR(Sprite& sp, DIR dir);	// ��ڲ԰�̍��E�ړ�
	void Jump(Sprite& sp, DIR dir);

	CREATE_FUNC(Player);

	// �ϐ�
	std::array<Vec2, static_cast<int>(DIR::MAX)>SpeedTbl;	// ��߰�ފi�[�pð���
	DIRArrayPair _offsetTbl;								// �����蔻��p�̾��ð���
private:
	// �֐�
	Animation* SetAnim(DIR dir);	// �����ɉ�������Ұ��݂̐ݒ�

	// �ϐ�
	Vec2 _pos;				// ��ڲ԰�̍��W	
	Size _size;				// ��ڲ԰�̑傫��

	bool _LRflag;			// ���E�m�F�p�@�E:false ��:true
	bool _jumpFancFlag;		// �ެ��ߒ�:true	�ެ��߂��Ă��Ȃ���:false

	int repeatNum;

	std::unique_ptr<OPRT_state>_inputState;
};

