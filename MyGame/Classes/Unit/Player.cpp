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
	// ｽﾌﾟﾗｲﾄｸﾗｽの初期化
	if (!Sprite::init())
	{
		return false;
	}
	// ｱﾆﾒｰｼｮﾝ
	// idle
	lpAnimMng.AnimCreate("player", "player-idle", 4, 0.1f);
	// run
	lpAnimMng.AnimCreate("player", "player-run", 10, 0.1f);
	// jump
	lpAnimMng.AnimCreate("player","player-jump", 6, 0.1f);

	auto visibleSize = Director::getInstance()->getVisibleSize();		// ｳｲﾝﾄﾞｳｻｲｽﾞ
	
	// ﾌﾟﾚｲﾔｰ初期設定
	this->Sprite::createWithSpriteFrameName("player-idle-1.png");
	auto Ppos = Vec2(visibleSize.width / 2, visibleSize.height / 2);	// ﾌﾟﾚｲﾔｰ初期位置
	this->setPosition(Ppos);
	LRflag = false;

	this->scheduleUpdate();

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	_inputState = std::make_unique<OPRT_key>(this);
#else
	_inputState.reset(new OPRT_touch(this));
	//_inputState = std::make_unique<OPRT_touch>();
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	
	return true;
}

void Player::update(float delta)
{
	auto directer = Director::getInstance();
	auto map = (TMXTiledMap*)directer->getRunningScene()->getChildByName("backLayer")->getChildByName("mapData");
	//int* num = (int*)malloc(sizeof(int) * 10);
	TMXLayer* colLayer = map->getLayer("footing");
	
	auto pSize = Size(60, 120);
	tileSize = Size(colLayer->getMapTileSize().width, colLayer->getMapTileSize().height); 
	mapTile = Size(map->getMapSize().width, map->getMapSize().height); 

	// ﾌﾟﾚｲﾔｰが埋まっていたら上に一応上げる処理@ｼﾞｬﾝﾌﾟ次第で削除するかも
	auto pPos = this->getPosition();
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
	
	if (col(*this, *map, { 0, -pSize.height / 2 - G })
	 && col(*this, *map,{ -pSize.width / 2, -pSize.height / 2 - G })
	 && col(*this, *map, { pSize.width / 2, -pSize.height / 2 - G }))
	{
		if (!jumpFancFlag)
		{
			this->setPosition(pPos.x, pPos.y - G);
		}
	}

	// ﾃﾞﾊﾞｯｸﾞ用 ※画面外の時落ちなかったため
	Vec2 pNextID = { pPos.x / tileSize.width,
					 mapTile.height - ((pPos.y - pSize.height / 2 - G) / tileSize.height) };	// ﾌﾟﾚｲﾔｰ座標次のID
	if (pNextID.y < 0)
	{
		this->setPosition(this->getPosition().x, this->getPosition().y - G);
		if (_inputState->GetData(DIR::RIGHT))
		{
			this->setPosition(this->getPosition().x + 5, this->getPosition().y);
		}
		if (_inputState->GetData(DIR::LEFT))
		{
			this->setPosition(this->getPosition().x - 5, this->getPosition().y);
		}
	}

	// ｱｸｼｮﾝとｱﾆﾒｰｼｮﾝ @関数分け予定
	Animation* animation = nullptr;	// ｱﾆﾒｰｼｮﾝ
	Action* animeAct = nullptr;		// ｱﾆﾒｰｼｮﾝ(リピートなど)
	Action* action = nullptr;
	Action* jumpAct = nullptr;
	
	auto speed = 5;
	//_inputState->Update();

	// ｼﾞｬﾝﾌﾟ 
	// ｺｰﾙﾊﾞｯｸ処理　ｼﾞｬﾝﾌﾟ中ﾌﾗｸﾞをfalseにする
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
			animeAct = Repeat::create(Animate::create(animation), 1);
			jumpFancFlag = true;
			jumpAct = Sequence::create(JumpBy::create(1.0f, { 0,0 }, 200, 1), callback, nullptr);			
			jumpAct->setTag(intCast(Tag::TRG_ACT));
		}
	}

	// 移動
	// 右
	if (_inputState->GetData(DIR::RIGHT))
	{
		LRflag = false;
		if (!jumpFancFlag)
		{
			animation = AnimationCache::getInstance()->getAnimation("player-run");
			animeAct = RepeatForever::create(Animate::create(animation));
		}
		if (col(*this, *map, { pSize.width / 2 + speed, - pSize.height / 2 })
			&& col(*this, *map, { pSize.width / 2 + speed, + pSize.height / 2}))
		{
			action = MoveBy::create(0, Vec2(speed, 0));
			action->setTag(intCast(Tag::ACT));
		}
	}
	// 左
	if (_inputState->GetData(DIR::LEFT))
	{
		LRflag = true;
		if (!jumpFancFlag)
		{
			animation = AnimationCache::getInstance()->getAnimation("player-run");
			animeAct = RepeatForever::create(Animate::create(animation));
		}
		if (col(*this, *map, { -pSize.width / 2 - speed, -pSize.height / 2 })
		 && col(*this, *map, { -pSize.width / 2 - speed, pSize.height / 2 }))
		{
			action =  MoveBy::create(0, Vec2(-speed, 0));
			action->setTag(intCast(Tag::ACT));
		}
	}

	// しゃがみ予定
	if (_inputState->GetData(DIR::DOWN))
	{
		if (col(*this, *map, { -pSize.width / 2, -pSize.height / 2 - speed })
		 && col(*this, *map, { pSize.width / 2, -pSize.height / 2 - speed }))
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
			animeAct = RepeatForever::create(Animate::create(animation));
		}
	}

	// ｱﾆﾒｰｼｮﾝrun
	if (animation != nullptr)
	{
		animeAct->setTag(intCast(Tag::ANIM));
		if (oldanim != animation)
		{
			this->stopActionByTag(intCast(Tag::ANIM));
			this->runAction(animeAct);
		}
	}
	// 描画左右反転
	if (LRflag != oldLRflag)
	{
		this->runAction(FlipX::create(LRflag));
	}
	// ｱｸｼｮﾝrun
	if (action != nullptr)
	{
		this->stopActionByTag(intCast(Tag::ACT));
		this->runAction(action);
	}
	// ｼﾞｬﾝﾌﾟrun
	if (jumpAct != nullptr)
	{
		if (jumpFlag)
		{
			this->runAction(jumpAct);
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

