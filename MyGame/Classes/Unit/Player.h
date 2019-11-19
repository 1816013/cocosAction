#pragma once
//#include "Obj.h"
#include <array>
#include <input/OPRT_state.h>
#include <ActionMng.h>



using DIRArrayPair = std::array<std::pair<Size, Size>, static_cast<int>(DIR::MAX)>;

class Player : public Sprite
{
public:
	// �֐�
	static cocos2d::Sprite* createSprite();
	Player();
	~Player();

	bool init()override;					// �������@���ײč쐬
	void update(float delta)override;		// ��ڲ԰�̈ړ��Ʊ�Ұ��ݏ���
	void Jump(Sprite& sp, DIR dir);			// �ެ���
	void Gravity(Sprite& sp);				// �d��
	void ChangeLR(Sprite& sp, DIR dir);		// ���E�؂�ւ�

	CREATE_FUNC(Player);
	std::unique_ptr<OPRT_state>_inputState;

	// �ϐ�
	std::array<Vec2, static_cast<int>(DIR::MAX)>SpeedTbl;	// ��߰�ފi�[�pð���
	DIRArrayPair _offsetTbl;								// �����蔻��p�̾��ð���
	std::shared_ptr<ActionMng>_actMng;
private:
	// �֐�
	Animation* SetAnim(DIR dir);	// �����ɉ�������Ұ��݂̐ݒ�

	// �ϐ�
	Vec2 _pos;				// ��ڲ԰�̍��W	
	Size _size;				// ��ڲ԰�̑傫��

	//bool _flagLR;			// ���E�m�F�p�@�E:false ��:true
	bool _jumpFancFlag;		// �ެ��ߒ�:true	�ެ��߂��Ă��Ȃ���:false
	int _repeatNum;

	
	// test
	Vec2 _speed = { 0, 0 };
	std::array<cocos2d::Size, 2>_colSize = { cocos2d::Size(0, 0), cocos2d::Size(0, 0)};

	
};

