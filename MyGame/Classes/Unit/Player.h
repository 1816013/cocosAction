#pragma once
//#include "Obj.h"
#include <array>
#include "input/OPRT_state.h"
#include "action/ActionMng.h"


using DIRArrayPair = std::array<std::pair<cocos2d::Size, cocos2d::Size>, static_cast<int>(DIR::MAX)>;

class Player : public cocos2d::Sprite
{
public:
	// �֐�
	static cocos2d::Sprite* createSprite();
	Player();
	~Player();

	bool init()override;				// �������@���ײč쐬
	void update(float delta)override;	// ��ڲ԰�̈ړ��Ʊ�Ұ��ݏ���
	void JumpSpeed(float speed);		// �ެ��߂̽�߰�ނ��擾����
	float JumpSpeed(void);				// �ެ��߂̽�߰�ނ�Ă���
	void ActState(ACT_STATE state);		// ��ڲ԰�̏�Ԃ�Ă���				
	ACT_STATE ActState(void);			// ��ڲ԰�̏�Ԃ��擾����

	CREATE_FUNC(Player);
	std::unique_ptr<OPRT_state>_inputState;

	

	// �ϐ�
	std::shared_ptr<ActionMng>_actMng;
	
private:
	// �֐�
	cocos2d::Animation* SetAnim(ACT_STATE state);	// �����ɉ�������Ұ��݂̐ݒ�

	// �ϐ�
	cocos2d::Vec2 _pos;				// ��ڲ԰�̍��W	
	cocos2d::Size _size;				// ��ڲ԰�̑傫��

	int _repeatNum;

	float _jumpSpeed;
	ACT_STATE _nowState;

	int count;
};

