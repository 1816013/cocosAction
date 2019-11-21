#pragma once
//#include "Obj.h"
#include <array>
#include <input/OPRT_state.h>
#include <ActionMng.h>

using DIRArrayPair = std::array<std::pair<cocos2d::Size, cocos2d::Size>, static_cast<int>(DIR::MAX)>;

class Player : public cocos2d::Sprite
{
public:
	// �֐�
	static cocos2d::Sprite* createSprite();
	Player();
	~Player();

	bool init()override;								// �������@���ײč쐬
	void update(float delta)override;					// ��ڲ԰�̈ړ��Ʊ�Ұ��ݏ���
	void Jump(cocos2d::Sprite& sp, DIR dir);			// �ެ���
	//void Gravity(Sprite& sp);							// �d��
	void ChangeLR(cocos2d::Sprite& sp, DIR dir);		// ���E�؂�ւ�
	void JumpSpeed(float speed);						// �ެ��߂̽�߰�ނ��擾����
	float JumpSpeed(void);								// �ެ��߂̽�߰�ނ�Ă���
	CREATE_FUNC(Player);
	std::unique_ptr<OPRT_state>_inputState;

	// �ϐ�
	std::shared_ptr<ActionMng>_actMng;
	float _jumpSpeed;
private:
	// �֐�
	cocos2d::Animation* SetAnim(DIR dir);	// �����ɉ�������Ұ��݂̐ݒ�

	// �ϐ�
	cocos2d::Vec2 _pos;				// ��ڲ԰�̍��W	
	cocos2d::Size _size;				// ��ڲ԰�̑傫��

	//bool _flagLR;			// ���E�m�F�p�@�E:false ��:true
	bool _jumpFancFlag;		// �ެ��ߒ�:true	�ެ��߂��Ă��Ȃ���:false
	int _repeatNum;


	
};

