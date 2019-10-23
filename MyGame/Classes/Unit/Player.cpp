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

	// run
	lpAnimMng.AnimCreate("player-run", 10, 0.1f);
	// jump
	lpAnimMng.AnimCreate("player-jump", 6, 0.1f);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto Ppos = Vec2(visibleSize.width / 2, visibleSize.height / 2);

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
	//col.reset(new Colision());
	
	return true;
}

void Player::update(float delta)
{
	auto directer = Director::getInstance();
	auto map = (TMXTiledMap*)directer->getRunningScene()->getChildByName("backLayer")->getChildByName("mapData");
	//int* num = (int*)malloc(sizeof(int) * 10);
	TMXLayer* colLayer = map->layerNamed("footing");
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
	auto pSize = Size(60, 120);
	tileSize = Size(colLayer->getMapTileSize().width, colLayer->getMapTileSize().height); 
	mapTile = Size(map->getMapSize().width, map->getMapSize().height); 
	/*_cPos[static_cast<int>(ConerPos::LEFT_UP)] = Vec2(pPos.x - pSize.width / 2, pPos.y + pSize.height / 2);
	_cPos[static_cast<int>(ConerPos::RIGHT_UP)] = Vec2(pPos.x + pSize.width / 2, pPos.y + pSize.height / 2);
	_cPos[static_cast<int>(ConerPos::RIGHT_DOWN)] = Vec2(pPos.x + pSize.width / 2, pPos.y - pSize.height / 2);
	_cPos[static_cast<int>(ConerPos::LEFT_DOWN)] = Vec2(pPos.x - pSize.width / 2, pPos.y - pSize.height / 2);*/

	// ﾌﾟﾚｲﾔｰが埋まっていたら上に一応上げる処理@削除するかも
	Vec2 pID;
	pID = { pPos.x / tileSize.width, 
		    mapTile.height - ((pPos.y - pSize.height / 2) / tileSize.height) };	// ﾌﾟﾚｲﾔｰ座標のID	
	if (pID.x < mapTile.width && pID.y < mapTile.height && pID.x > 0 && pID.y > 0)
	{
		if (colLayer->getTileGIDAt({ pID.x, pID.y}) != 0)
		{
			this->setPosition(pPos.x, pPos.y + (pPos.y - ((mapTile.height - pID.y + 1 ) *  tileSize.height)));
			//TRACE("HIT%d\n", hitc++);				
		}
	}

	// 重力
	auto G = 10;
	Vec2 pNextID = { pPos.x / tileSize.width, 
					 mapTile.height - ((pPos.y - pSize.height / 2 - G) / tileSize.height) };	// ﾌﾟﾚｲﾔｰ座標次のID
	if (col(pNextID, *colLayer, mapTile))
	{
		if (!jumpFancFlag)
		{
			this->setPosition(pPos.x, pPos.y - G);
		}
	}

	// ﾃﾞﾊﾞｯｸﾞ用 ※画面外の時落ちなかったため
	if (pNextID.y < 0)
	{
		this->setPosition(this->getPosition().x, this->getPosition().y - G);
	}
	// move & animation @関数分け予定
	Action* anime = nullptr;
	Action* action = nullptr;
	Action* jump = nullptr;
	Animation* animation = nullptr;
	auto speed = 5;
	//_inputState->Update();
	
	// jump 
	auto callback = CallFunc::create([this]()
	{
		jumpFancFlag = false;
	});
	if (_inputState->GetData(DIR::UP))
	{
		if (!jumpFancFlag)
		{
			jumpFlag = true;
			animation = AnimationCache::getInstance()->getAnimation("player-jump");
			anime = Repeat::create(Animate::create(animation), 1);
			jumpFancFlag = true;
			jump = Sequence::create(JumpBy::create(1.0f, { 0,0 }, 200, 1), callback, nullptr);			
			jump->setTag(intCast(Tag::TRG_ACT));
		}
		
	}

	// 移動
	if (_inputState->GetData(DIR::RIGHT))
	{
		LRflag = false;
		if (!jumpFancFlag)
		{
			animation = AnimationCache::getInstance()->getAnimation("player-run");
			anime = RepeatForever::create(Animate::create(animation));
		}
		MoveBy* move;
		pNextID = { (pPos.x + pSize.width / 2 + speed) / tileSize.width,
					 mapTile.height - ((pPos.y - pSize.height / 2) / tileSize.height) };	// ﾌﾟﾚｲﾔｰ座標次のID
		if (col(pNextID, *colLayer, mapTile))
		{
			move = MoveBy::create(0, Vec2(speed, 0));
			action = Spawn::create(FlipX::create(LRflag), move, nullptr);	
			action->setTag(intCast(Tag::ACT));
		}
		else
		{
			action = FlipX::create(LRflag);
			action->setTag(intCast(Tag::ACT));
		}		
	}

	// 左移動
	if (_inputState->GetData(DIR::LEFT))
	{
		LRflag = true;
		if (!jumpFancFlag)
		{
			animation = AnimationCache::getInstance()->getAnimation("player-run");
			anime = RepeatForever::create(Animate::create(animation));
		}
		pNextID = { (pPos.x - pSize.width / 2 - speed) / tileSize.width,
					 mapTile.height - ((pPos.y - pSize.height / 2) / tileSize.height) };	// ﾌﾟﾚｲﾔｰ座標次のID
		if (col(pNextID, *colLayer, mapTile))
		{
			auto move = MoveBy::create(0, Vec2(-speed, 0));
			action = Spawn::create(FlipX::create(LRflag), move, nullptr);
			action->setTag(intCast(Tag::ACT));
		}
		else
		{
			action = FlipX::create(LRflag);
			action->setTag(intCast(Tag::ACT));
		}

	}

	// しゃがみ予定
	if (_inputState->GetData(DIR::DOWN))
	{
		pNextID = { (pPos.x + pSize.width / 2) / tileSize.width,
					 mapTile.height - ((pPos.y - pSize.height / 2 - speed) / tileSize.height) };	// ﾌﾟﾚｲﾔｰ座標次のID
		if (col(pNextID, *colLayer, mapTile))
		{
			this->setPosition(this->getPosition().x, this->getPosition().y - speed);
		}	
		this->setPosition(this->getPosition().x, this->getPosition().y - speed);
	}
	
	// 待機
	if (animation == nullptr)
	{
		if (!jumpFancFlag)
		{
			animation = AnimationCache::getInstance()->getAnimation("player-idle");
			anime = RepeatForever::create(Animate::create(animation));
			action = Spawn::create(FlipX::create(LRflag), nullptr);
			action->setTag(intCast(Tag::ACT));
		}
	}
	// ｱﾆﾒｰｼｮﾝ
	if (animation != nullptr)
	{
		if(anime->getTag() == -1)
		{ 
			anime->setTag(intCast(Tag::ANIM));
		}
		if (oldanim != animation || oldLRflag != LRflag)
		{
			this->stopActionByTag(intCast(Tag::ANIM));
			this->runAction(anime);
		}
	}

	if (action != nullptr)
	{
		this->stopActionByTag(intCast(Tag::ACT));
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

//bool Player::Colision(const Vec2 ID,  TMXLayer & col)
//{
//	if (ID.x < mapTile.width && ID.y < mapTile.height && ID.x > 0 && ID.y > 0)
//	{
//		if (col.getTileGIDAt({ ID.x, ID.y }) == 0)
//		{		
//			return true;
//		}
//	}
//	return false;
//}

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

