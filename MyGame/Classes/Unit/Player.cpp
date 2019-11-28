#include "Player.h"
#include "AnimMng.h"
#include <input/OPRT_key.h>
#include <input/OPRT_touch.h>
#include <action/Colision.h>
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include "_debug/_DebugConOut.h"
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)


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
	// ｽﾌﾟﾗｲﾄｸﾗｽの初期化@initを自作したため必要
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

	// ｱﾆﾒｰｼｮﾝ設定
	lpAnimMng.AnimCreate("player", "idle", 4, 0.1f);	// 待機	
	lpAnimMng.AnimCreate("player", "run", 10, 0.1f);	// 走る
	lpAnimMng.AnimCreate("player", "jump", 6, 0.05f);	// ｼﾞｬﾝﾌﾟ
	lpAnimMng.AnimCreate("player", "duck", 1, 0.1f);	// しゃがみ
	lpAnimMng.AnimCreate("player", "stand", 3, 0.1f);	// 落下(立ち上がり)
	
	// ｴﾌｪｸﾄ
	auto visibleSize = Director::getInstance()->getVisibleSize();		// ｳｲﾝﾄﾞｳｻｲｽﾞ	
	

	// ﾌﾟﾚｲﾔｰ初期設定
	this->Sprite::createWithSpriteFrameName("player-idle-1.png");	// ﾌﾟﾚｲﾔｰの初期画像
	_pos = Vec2(visibleSize.width / 2, visibleSize.height / 2 +50);	// ﾌﾟﾚｲﾔｰ初期位置
	_size = Size(60, 120);
	this->setPosition(_pos);
	this->setContentSize(_size);
	_jumpSpeed = 0.0f;
	_nowState = ACT_STATE::IDLE;
	// 左移動
	{
		actModule module;
		module.actID = ACT_STATE::RUN;
		module.speed = Vec2(-5, 0);
		module.colSize = { Size(-30, 45), Size(-30, -60) };
		module.keyCode = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
		module.keyMode = TRG_STATE::NOW;
		module.keyTiming = Timing::ON;
		_actMng->AddActModule("左移動", module);
	}

	// 右移動
	{
		actModule module;
		module.actID = ACT_STATE::RUN;
		module.speed = Vec2(5, 0);
		module.colSize = { Size(30, 45), Size(30, -60) };
		module.keyCode = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
		module.keyMode = TRG_STATE::NOW;
		module.keyTiming = Timing::ON;
		_actMng->AddActModule("右移動", module);
	}
	// ｼﾞｬﾝﾌﾟ
	{
		actModule module;
		module.actID = ACT_STATE::JUMP;
		module.black.emplace_back(ACT_STATE::JUMPING);
		module.black.emplace_back(ACT_STATE::FALLING);
		module.black.emplace_back(ACT_STATE::JUMP);
		module.keyCode = EventKeyboard::KeyCode::KEY_UP_ARROW;
		module.keyMode = TRG_STATE::NOW;
		module.keyTiming = Timing::ON_MOM;
		_actMng->AddActModule("ｼﾞｬﾝﾌﾟ", module);
	}
	// ｼﾞｬﾝﾌﾟ中
	{
		actModule module;
		module.actID = ACT_STATE::JUMPING;
		module.black.emplace_back(ACT_STATE::FALLING);
		module.black.emplace_back(ACT_STATE::FALL);
		module.speed = Vec2(0, _jumpSpeed);
		module.colSize = { Size(30, 45), Size(-30, 40) };
		_actMng->AddActModule("ｼﾞｬﾝﾌﾟ中", module);
	}
	// 落下
	{
		actModule module;
		module.actID = ACT_STATE::FALL;
		module.black.emplace_back(ACT_STATE::IDLE);
		module.black.emplace_back(ACT_STATE::FALLING);
		module.black.emplace_back(ACT_STATE::JUMP);
		module.colSize = { Size(30, -60), Size(-30, -60) };
		module.speed = Vec2(0, -5);
		_actMng->AddActModule("落下", module);
	}
	// 落下中
	{
		actModule module;
		module.actID = ACT_STATE::FALLING;
		module.black.emplace_back(ACT_STATE::JUMPING);
		module.speed = Vec2(0, -5);
		module.colSize = { Size(30, -60), Size(-30, -60) };
		_actMng->AddActModule("落下中", module);
	}
	// 向き変更左
	{
		actModule module;
		module.actID = ACT_STATE::CHANGE_LEFT;
		module.keyCode = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
		module.keyMode = TRG_STATE::NOW;
		module.keyTiming = Timing::ON;
		_actMng->AddActModule("左向き", module);
	}
	// 向き変更右
	{
		actModule module;
		module.actID = ACT_STATE::CHANGE_RIGHT;
		module.keyCode = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
		module.keyMode = TRG_STATE::NOW;
		module.keyTiming = Timing::ON;
		_actMng->AddActModule("右向き", module);
	}

	this->scheduleUpdate();
	return true;
}

void Player::update(float delta)
{
	_inputState->update();
	_actMng->update(*this);
	
	auto anim = SetAnim(_nowState);	// repeatNumの設定をSetAnimで設定しているため先読み必須@変更予定
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
		if (state == ACT_STATE::FALL || state == ACT_STATE::FALLING)
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