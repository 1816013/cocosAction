#include "Player.h"
#include "AnimMng.h"
#include <input/OPRT_key.h>
#include <input/OPRT_touch.h>
//#include "_DebugConOut.h"

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
	// ｱﾆﾒｰｼｮﾝ
	// idle
	lpAnimMng.AnimCreate("player-idle", 4, 0.1f );
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
	lpAnimMng.AnimCreate("player-run", 10, 0.1f);
	// jump

	//auto sprite = Sprite::createWithSpriteFrameName("player-jump-1.png");
	// position the sprite on the center of the screen
	//player->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	// add the sprite as a child to this layer
	//this->addChild(sprite, 0);
	// �A�j���[�V����
	lpAnimMng.AnimCreate("player-jump", 6, 0.1f);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto Ppos = Vec2(48,96);

	// ﾌﾟﾚｲﾔｰ初期設定
	this->Sprite::createWithSpriteFrameName("player-idle-1.png");
	// position the sprite on the center of the screen
	this->setPosition(Ppos);
	//this->setScale(2.0f);
	LRflag = false;

	this->scheduleUpdate();

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	_inputState = std::make_unique<OPRT_key>(this);
	//state = new(OPRT_key);
#else
	_inputState.reset(new OPRT_touch(this));
	//_inputState = std::make_unique<OPRT_touch>();
	//state = new(OPRT_touch);
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)


	return true;
}

void Player::update(float delta)
{
	// colision
	auto directer = Director::getInstance();
	auto map = (TMXTiledMap*)directer->getRunningScene()->getChildByName("backLayer")->getChildByName("mapData");
	//int* num = (int*)malloc(sizeof(int) * 10);
	auto col = map->layerNamed("footing");
	//auto colF = col->propertyNamed("colision").asBool();
	//if (colGID.size() == 0)
	//{
	//	for (float y = 0; y < map->getMapSize().height; y++)
	//	{
	//		for (float x = 0; x < map->getMapSize().width; x++)
	//		{
	//			colGID.emplace_back(col->getTileGIDAt({ x, y }));
	//			//colGID[x + y * map->getMapSize().width] = ;
	//		}
	//	}
	//}
	
	auto pPos = this->getPosition();
	auto pSize = Vec2(60, 120);

	_cPos[static_cast<int>(ConerPos::LEFT_UP)] = Vec2(pPos.x - pSize.x / 2, pPos.y + pSize.y / 2);
	_cPos[static_cast<int>(ConerPos::RIGHT_UP)] = Vec2(pPos.x + pSize.x / 2, pPos.y + pSize.y / 2);
	_cPos[static_cast<int>(ConerPos::RIGHT_DOWN)] = Vec2(pPos.x + pSize.x / 2, pPos.y - pSize.y / 2);
	_cPos[static_cast<int>(ConerPos::LEFT_DOWN)] = Vec2(pPos.x - pSize.x / 2, pPos.y - pSize.y / 2);

	
	Vec2 pID;
	pID = { pPos.x / col->getMapTileSize().width, map->getMapSize().height - ((pPos.y - 75) / col->getMapTileSize().height) };
	if (pID.x < map->getMapSize().width && pID.y < map->getMapSize().height && pID.x > 0 && pID.y > 0)
	{
		if (col->getTileGIDAt({ pID.x, pID.y }) != 0)
		{
			this->setPosition(pPos.x, pPos.y + 10);
			//TRACE("HIT%d\n", hitc++);
		}
		else
		{
			this->setPosition(pPos.x, pPos.y - 10);
		}
	}
	

	// move & animation
	Action* anime = nullptr;
	Action* action = nullptr;
	Action* jump = nullptr;
	Animation* animation = oldanim;

	//_inputState->Update();
	auto speed = 3;

	auto callback = CallFunc::create([this]()
	{
		jumpFancFlag = false;
	});
	if (_inputState->GetData(DIR::UP))
	{
		jumpFlag = true;
		animation = AnimationCache::getInstance()->getAnimation("player-jump");
		anime = Repeat::create(Animate::create(animation), 1);
		jump = Sequence::create(JumpBy::create(1.0f, { 0,0 }, 70, 1), callback, nullptr);
		anime->setTag(0);
		jump->setTag(2);
		jumpFancFlag = true;
		jumpTime = 0;	
	}
	if (_inputState->GetData(DIR::RIGHT))
	{
		LRflag = false;
		if (!jumpFancFlag)
		{
			
			animation = AnimationCache::getInstance()->getAnimation("player-run");
			anime = RepeatForever::create(Animate::create(animation));
			anime->setTag(0);
		}
		auto move = MoveBy::create(0, Vec2(5, 0));
		action = Spawn::create(FlipX::create(LRflag), move, nullptr);
			
		action->setTag(1);
		
	}
	if (_inputState->GetData(DIR::DOWN))
	{
		this->setPosition(this->getPosition().x, this->getPosition().y - 5);
		/*if (!jumpFancFlag)
		{
			animation = AnimationCache::getInstance()->getAnimation("player-idle");
			anime = RepeatForever::create(Animate::create(animation));
			action = Spawn::create(FlipX::create(LRflag), nullptr);
			anime->setTag(0);
			action->setTag(1);
		}*/
	}
	if (_inputState->GetData(DIR::LEFT))
	{
		LRflag = true;
		if (!jumpFancFlag)
		{
			
			animation = AnimationCache::getInstance()->getAnimation("player-run");
			anime = RepeatForever::create(Animate::create(animation));
			anime->setTag(0);
		}
		auto move = MoveBy::create(0, Vec2(-5, 0));
		action = Spawn::create(FlipX::create(LRflag), move, nullptr);
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
		if (!jumpFancFlag)
		{
			animation = AnimationCache::getInstance()->getAnimation("player-idle");
			anime = RepeatForever::create(Animate::create(animation));
			anime->setTag(0);
			action = Spawn::create(FlipX::create(LRflag), nullptr);
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
	oldLRflag = LRflag;
	oldanim = animation;
}

//bool Player::AnimCreate(std::string key, int cnt, float time )
//{
//	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(key + ".plist");
//	auto animation = Animation::create();
//	for (int i = 1; i <= cnt; i++)
//	{
//		auto str = __String::createWithFormat((key + "-%i.png").c_str(), i);
//		SpriteFrame *sprite = SpriteFrameCache::getInstance()->getSpriteFrameByName(str->getCString());
//		animation->addSpriteFrame(sprite);
//	}
//
//	animation->setDelayPerUnit(time); // ｱﾆﾒｰｼｮﾝの期間
//	animation->setRestoreOriginalFrame(true);	// ｱﾆﾒｰｼｮﾝ終了時に初めに戻るか
//
//	AnimationCache::getInstance()->addAnimation(animation, key);
//	return true;
//}

