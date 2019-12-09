#include "Player.h"
#include "AnimMng.h"
#include <input/OPRT_key.h>
#include <input/OPRT_touch.h>
#include <action/Colision.h>
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include "_debug/_DebugConOut.h"
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "EffectMng.h"



USING_NS_CC;

cocos2d::Sprite * Player::createSprite()
{
	return Player::create();
}

Player::Player()
{

}

Player::~Player()
{
}

bool Player::init()
{
	// ���ײĸ׽�̏�����@init�����삵�����ߕK�v
	if (!Sprite::init())
	{
		return false;
	}

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32	
	_inputState = std::make_unique<OPRT_key>(this);
	_actMng = std::make_shared<ActionMng>();
#else
	_inputState.reset(new OPRT_touch(this));
	_actMng.reset(new ActionMng());
	//_inputState = std::make_unique<OPRT_touch>();
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

	// ��Ұ��ݐݒ�
	lpAnimMng.AnimCreate("player", "idle", 4, 0.1f);	// �ҋ@	
	lpAnimMng.AnimCreate("player", "run", 10, 0.1f);	// ����
	lpAnimMng.AnimCreate("player", "jump", 6, 0.05f);	// �ެ���
	lpAnimMng.AnimCreate("player", "duck", 1, 0.1f);	// ���Ⴊ��
	lpAnimMng.AnimCreate("player", "stand", 3, 0.1f);	// ����(�����オ��)
	
	// �̪��
	auto visibleSize = Director::getInstance()->getVisibleSize();		// ����޳����	
	

	// ��ڲ԰�����ݒ�
	this->Sprite::createWithSpriteFrameName("player-idle-1.png");	// ��ڲ԰�̏����摜
	_pos = Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50);	// ��ڲ԰�����ʒu
	_size = Size(60, 120);
	this->setPosition(_pos);
	this->setContentSize(_size);
	_jumpSpeed = 0.0f;
	_nowState = ACT_STATE::IDLE;

	// ����ݾ�� @csv�o�͂ɂ�����
	// ���ړ�
	{
		actModule module;
		module.actID = ACT_STATE::RUN;
		module.speed = Vec2(-5, 0);
		module.colSize = { Size(-30, 45), Size(-30, -60) };
		module.inputID = INPUT_ID::LEFT;
		module.keyMode = TRG_STATE::NOW;
		module.keyTiming = Timing::ON;
		_actMng->AddActModule("���ړ�", module);
	}

	// �E�ړ�
	{
		actModule module;
		module.actID = ACT_STATE::RUN;
		module.speed = Vec2(5, 0);
		module.colSize = { Size(30, 45), Size(30, -60) };
		module.inputID = INPUT_ID::RIGHT;
		module.keyMode = TRG_STATE::NOW;
		module.keyTiming = Timing::ON;
		_actMng->AddActModule("�E�ړ�", module);
	}	
	// ����
	{
		actModule module;
		module.actID = ACT_STATE::FALL;
		module.black.emplace_back(ACT_STATE::FALLING);
		module.black.emplace_back(ACT_STATE::JUMP);
		module.colSize = { Size(30, -60), Size(-30, -60) };
		_actMng->AddActModule("����", module);
	}
	// ������
	{
		actModule module;
		module.actID = ACT_STATE::FALLING;
		module.black.emplace_back(ACT_STATE::JUMPING);
		module.black.emplace_back(ACT_STATE::JUMP);
		module.colSize = { Size(30, -60), Size(-30, -60) };
		_actMng->AddActModule("������", module);
	}
	// �ެ���
	{
		actModule module;
		module.actID = ACT_STATE::JUMP;
		module.black.emplace_back(ACT_STATE::JUMPING);
		module.black.emplace_back(ACT_STATE::FALLING);
		module.black.emplace_back(ACT_STATE::FALL);
		module.black.emplace_back(ACT_STATE::SHOT);
		module.inputID = INPUT_ID::UP;
		module.keyMode = TRG_STATE::NOW;
		module.keyTiming = Timing::ON_MOM;
		_actMng->AddActModule("�ެ���", module);
	}
	// �ެ��ߒ�
	{
		actModule module;
		module.actID = ACT_STATE::JUMPING;
		module.black.emplace_back(ACT_STATE::FALLING);
		module.black.emplace_back(ACT_STATE::IDLE);
		module.speed = Vec2(0, 0);
		module.colSize = { Size(30, 40), Size(-30, 40) };
		_actMng->AddActModule("�ެ��ߒ�", module);
	}
	
	// �����ύX��
	{
		actModule module;
		module.actID = ACT_STATE::CHANGE_LEFT;
		module.inputID = INPUT_ID::LEFT;
		module.keyMode = TRG_STATE::NOW;
		module.keyTiming = Timing::ON;
		_actMng->AddActModule("������", module);
	}
	// �����ύX�E
	{
		actModule module;
		module.actID = ACT_STATE::CHANGE_RIGHT;
		module.inputID = INPUT_ID::RIGHT;
		module.keyMode = TRG_STATE::NOW;
		module.keyTiming = Timing::ON;
		_actMng->AddActModule("�E����", module);
	}
	// ����
	{
		actModule module;
		module.actID = ACT_STATE::SHOT;
		module.white.emplace_back(ACT_STATE::IDLE);
		module.black.emplace_back(ACT_STATE::JUMPING);
		module.inputID = INPUT_ID::SHOT;
		module.keyMode = TRG_STATE::NOW;
		module.keyTiming = Timing::ON;
		_actMng->AddActModule("����", module);
	}

	this->scheduleUpdate();
	count = 0;
	return true;
}

void Player::update(float delta)
{
	_inputState->update();
	_actMng->update(*this);
	//TRACE("%d\n", _nowState);
	auto anim = SetAnim(_nowState);	// repeatNum�̐ݒ��SetAnim�Őݒ肵�Ă��邽�ߐ�ǂݕK�{@�ύX�\��
	lpAnimMng.runAnim(*this, *anim, _repeatNum);	
}

void Player::JumpSpeed(float speed)
{
	_jumpSpeed = speed;
}

float Player::JumpSpeed(void)
{
	return _jumpSpeed;
}

void Player::ActState(ACT_STATE state)
{
	_nowState = state;
}

ACT_STATE Player::ActState(void)
{
	return _nowState;
}

Animation* Player::SetAnim(ACT_STATE state)
{
	auto animCache = AnimationCache::getInstance();
	Animation* anim = nullptr;
	_repeatNum = 0;
	if (state == ACT_STATE::JUMP || state == ACT_STATE::JUMPING)
	{
		anim = animCache->getAnimation("jump");
		_repeatNum = 1;
	}

	if (anim != animCache->getAnimation("jump"))
	{
		if (state == ACT_STATE::RUN)
		{
			anim = animCache->getAnimation("run");
		}
		if (state == ACT_STATE::FALL || state == ACT_STATE::FALLING || state == ACT_STATE::SHOT)
		{
			anim = animCache->getAnimation("stand");
			
		}
		if (anim == nullptr && state == ACT_STATE::IDLE)
		{
			anim = animCache->getAnimation("idle");
		}
	}
	
	return anim;
}