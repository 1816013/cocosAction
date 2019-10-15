#include "Player.h"
#include <input/OPRT_key.h>
#include <input/OPRT_touch.h>

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
	// 1. super init first
	if (!Sprite::init())
	{
		return false;
	}
	

	// plist読み込み
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("player-idle.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("player-run.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("player-jump.plist");
	
	// idle
	AnimCreate("player-idle", 4, 0.1f );
	//auto animation = Animation::create();
	//for (int i = 1; i <= 4; i++) 
	//{
	//	auto str = __String::createWithFormat("player-idle-%i.png", i);
	//	SpriteFrame *sprite = SpriteFrameCache::getInstance()->getSpriteFrameByName(str->getCString());
	//	animation->addSpriteFrame(sprite);
	//}
	//animation->setDelayPerUnit(0.2f); //�A�j���̓������Ԃ�ݒ�
	//animation->setRestoreOriginalFrame(true);	// ��Ұ��ݏI�����ɱ�Ұ��݂̍ŏ��ɖ߂邩�ǂ���
	//AnimationCache::getInstance()->addAnimation(animation, "idle");
	//auto action = Animate::create(animation);
	//auto anime = RepeatForever::create(action);
	//oldanim = animation;
	//player->runAction(anime);*/

	// run
	AnimCreate("player-run", 10, 0.1f);
	// jump

	//auto sprite = Sprite::createWithSpriteFrameName("player-jump-1.png");
	// position the sprite on the center of the screen
	//player->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	// add the sprite as a child to this layer
	//this->addChild(sprite, 0);
	// �A�j���[�V����
	AnimCreate("player-jump", 6, 0.1f);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto pos = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

	// ﾌﾟﾚｲﾔｰ初期設定
	this->Sprite::createWithSpriteFrameName("player-idle-1.png");
	// position the sprite on the center of the screen
	this->setPosition(pos);
	//this->setScale(2.0f);
	LRflag = false;


	this->scheduleUpdate();

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	_inputState = std::make_unique<OPRT_key>();
	//state = new(OPRT_key);
#else
	_inputState.reset(new OPRT_touch());
	//_inputState = std::make_unique<OPRT_touch>();
	//state = new(OPRT_touch);
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)


	return true;
}

void Player::update(float delta)
{
	Action* anime = nullptr;
	Action* action = nullptr;
	Action* jump = nullptr;

	Animation* animation = oldanim;
	_inputState->Update(this);
	auto speed = 3;
	if (_inputState->GetData(DIR::UP))
	{
		jumpFlag = true;
		//player->setPosition(pos.x, pos.y += speed);
		animation = AnimationCache::getInstance()->getAnimation("player-jump");
		anime = Repeat::create(Animate::create(animation), 1);
		jump = Spawn::create(JumpBy::create(1.0f, { 0,0 }, 50, 1), nullptr);
		anime->setTag(0);
		jump->setTag(2);
		jumpTimeFlag = true;
		jumpTime = 0;
		//anime = Spawn::create(anim, jump, nullptr);
	}
	if (_inputState->GetData(DIR::RIGHT))
	{
		LRflag = false;
		animation = AnimationCache::getInstance()->getAnimation("player-run");
		anime = RepeatForever::create(Animate::create(animation));
		auto move = MoveBy::create(0, Vec2(1, 0));
		action = Spawn::create(FlipX::create(LRflag), move, nullptr);
		anime->setTag(0);
		action->setTag(1);
	}
	if (_inputState->GetData(DIR::DOWN))
	{
		animation = AnimationCache::getInstance()->getAnimation("player-idle");
		anime = RepeatForever::create(Animate::create(animation));
		action = Spawn::create(FlipX::create(LRflag), nullptr);
		anime->setTag(0);
		action->setTag(1);
	}
	if (_inputState->GetData(DIR::LEFT))
	{
		LRflag = true;
		animation = AnimationCache::getInstance()->getAnimation("player-run");
		anime = RepeatForever::create(Animate::create(animation));
		auto move = MoveBy::create(0, Vec2(-1, 0));
		action = Spawn::create(FlipX::create(LRflag), move, nullptr);
		anime->setTag(0);
		action->setTag(1);

	}
	/*if (!_inputState->GetData(DIR::UP) && !_inputState->GetData(DIR::RIGHT) && !_inputState->GetData(DIR::DOWN) && !_inputState->GetData(DIR::LEFT) || _inputState->GetData(DIR::RIGHT) && _inputState->GetData(DIR::LEFT))
	{
		if (!jumpTimeFlag)
		{
			animation = AnimationCache::getInstance()->getAnimation("idle");
			anime = RepeatForever::create(Animate::create(animation));
			action = Spawn::create(FlipX::create(LRflag), nullptr);
			anime->setTag(0);
			action->setTag(1);
		}
	}*/
	if (anime == nullptr)
	{
		if (!jumpTimeFlag)
		{
			animation = AnimationCache::getInstance()->getAnimation("player-idle");
			anime = RepeatForever::create(Animate::create(animation));
			action = Spawn::create(FlipX::create(LRflag), nullptr);
			anime->setTag(0);
			action->setTag(1);
		}
	}

	if (anime != nullptr)
	{
		if (oldanim != animation || oldLRflag != LRflag)
		{
			this->stopActionByTag(0);
			this->runAction(anime);
		}
	}

	if (action != nullptr)
	{
		this->stopActionByTag(1);
		this->runAction(action);	
	}

	if (jump != nullptr)
	{
		if (jumpFlag)
		{
			
			this->runAction(jump);
			jumpFlag = false;
		}
	}
	if (jumpTimeFlag)
	{
		jumpTime++;
	}
	if (jumpTime > 60)
	{
		jumpTimeFlag = false;
	}
	oldLRflag = LRflag;
	oldanim = animation;
}

bool Player::AnimCreate(std::string key, int cnt, float time )
{
	auto animation = Animation::create();
	for (int i = 1; i <= cnt; i++)
	{
		auto str = __String::createWithFormat((key + "-%i.png").c_str(), i);
		SpriteFrame *sprite = SpriteFrameCache::getInstance()->getSpriteFrameByName(str->getCString());
		animation->addSpriteFrame(sprite);
	}

	animation->setDelayPerUnit(time); // ｱﾆﾒｰｼｮﾝの期間
	animation->setRestoreOriginalFrame(true);	// ｱﾆﾒｰｼｮﾝ終了時に初めに戻るか

	AnimationCache::getInstance()->addAnimation(animation, key);
	return true;
}

