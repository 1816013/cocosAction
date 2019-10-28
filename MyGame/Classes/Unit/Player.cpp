#include "Player.h"
#include "AnimMng.h"
#include <input/OPRT_key.h>
#include <input/OPRT_touch.h>
#include <Colision.h>

//#include "_DebugConOut.h"

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
	// ｱﾆﾒｰｼｮﾝ設定
	lpAnimMng.AnimCreate("player", "idle", 4, 0.1f);	// 待機	
	lpAnimMng.AnimCreate("player", "run", 10, 0.1f);	// 走る
	lpAnimMng.AnimCreate("player","jump", 6, 0.1f);		// ｼﾞｬﾝﾌﾟ
	lpAnimMng.AnimCreate("player", "duck", 1, 0.1f);	// しゃがみ

	
	// ﾌﾟﾚｲﾔｰ初期設定
	this->Sprite::createWithSpriteFrameName("player-idle-1.png");	// ﾌﾟﾚｲﾔｰの初期画像

	auto visibleSize = Director::getInstance()->getVisibleSize();		// ｳｲﾝﾄﾞｳｻｲｽﾞ	
	_pos = Vec2(visibleSize.width / 2, visibleSize.height / 2);	// ﾌﾟﾚｲﾔｰ初期位置
	_size = Size(60, 120);
	this->setPosition(_pos);
	
	_LRflag = false;						
	_oldLRflag = _LRflag;					
	_jumpFlag = false;						
	_jumpFancFlag = false;					

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
	_pos = this->getPosition();
	auto directer = Director::getInstance();
	auto map = (TMXTiledMap*)directer->getRunningScene()->getChildByName("backLayer")->getChildByName("mapData");
	//int* num = (int*)malloc(sizeof(int) * 10);

	// ﾃﾞﾊﾞｯｸﾞ用 ※
	// ﾌﾟﾚｲﾔｰが埋まっていたら上に一応上げる処理@ｼﾞｬﾝﾌﾟ次第で削除するかも※
	TMXLayer* colLayer = map->getLayer("footing");
	auto tileSize = Size(colLayer->getMapTileSize().width, colLayer->getMapTileSize().height);
	auto mapTile = Size(map->getMapSize().width, map->getMapSize().height);
	Vec2 pID;
	pID = { _pos.x / tileSize.width,
			mapTile.height - ((_pos.y - _size.height / 2) / tileSize.height) };	// ﾌﾟﾚｲﾔｰ座標のID	
	if (pID.x < mapTile.width && pID.y < mapTile.height && pID.x > 0 && pID.y > 0)
	{
		if (colLayer->getTileGIDAt({ pID.x, pID.y}) != 0)
		{
			this->setPosition(_pos.x, _pos.y + (_pos.y - ((mapTile.height - pID.y + 1 ) *  tileSize.height)));
			//TRACE("HIT%d\n", hitc++);				
		}
	}
	Vec2 pNextID = { _pos.x / tileSize.width,
					 mapTile.height - ((_pos.y - _size.height) / tileSize.height) };	// ﾌﾟﾚｲﾔｰ座標のID
	if (pNextID.y < 0)
	{
		this->setPosition(this->getPosition().x, this->getPosition().y - 10);
		if (_inputState->GetData(DIR::RIGHT))
		{
			this->setPosition(this->getPosition().x + 5, this->getPosition().y);
		}
		if (_inputState->GetData(DIR::LEFT))
		{
			this->setPosition(this->getPosition().x - 5, this->getPosition().y);
		}
	}
	//※

	auto G = 10;
	// 重力
	if (Colision()(*this, { 0, -_size.height / 2 - G })						// 足元の中心
	 && Colision()(*this,{ -_size.width / 2, -_size.height / 2 - G })			// 足元の左
	 && Colision()(*this,{ _size.width / 2, -_size.height / 2 - G }))		// 足元の右
	{
		if (!_jumpFancFlag)
		{
			this->setPosition(_pos.x, _pos.y - G);
		}
	}

	// ｱｸｼｮﾝとｱﾆﾒｰｼｮﾝ @関数分け予定
	Animation* animation = nullptr;	// ｱﾆﾒｰｼｮﾝ
	Action* animeAct = nullptr;		// ｱﾆﾒｰｼｮﾝ(リピートなど)
	Action* action = nullptr;		// ｱｸｼｮﾝ
	Action* jumpAct = nullptr;		// ｼﾞｬﾝﾌﾟ@ﾄﾘｶﾞｰ処理のｱｸｼｮﾝ	
	auto speed = 5;					// ﾌﾟﾚｲﾔｰのｽﾋﾟｰﾄﾞ
	//_inputState->Update();

	// ｼﾞｬﾝﾌﾟ 
	// ｺｰﾙﾊﾞｯｸ処理　ｼﾞｬﾝﾌﾟ中ﾌﾗｸﾞをfalseにする
	auto callback = CallFunc::create([this]()
	{
		_jumpFancFlag = false;
	});

	if (_inputState->GetData(DIR::UP))
	{
		if (!_jumpFancFlag)
		{			
			animation = AnimationCache::getInstance()->getAnimation("jump");
			animeAct = Repeat::create(Animate::create(animation), 1);

			_jumpFlag = true;
			_jumpFancFlag = true;
			jumpAct = Sequence::create(JumpBy::create(1.0f, { 0,0 }, 200, 1), callback, nullptr);			
			jumpAct->setTag(intCast(Tag::TRG_ACT));
			
		}
	}

	// 移動
	// 右
	if (_inputState->GetData(DIR::RIGHT))
	{
		_LRflag = false;
		if (!_jumpFancFlag)
		{
			animation = AnimationCache::getInstance()->getAnimation("run");
			animeAct = RepeatForever::create(Animate::create(animation));
		}
		if (Colision()(*this, { _size.width / 2 + speed, - _size.height / 2 })
			&& Colision()(*this, { _size.width / 2 + speed, + _size.height / 2}))
		{
			action = MoveBy::create(0, Vec2(speed, 0));
			action->setTag(intCast(Tag::ACT));
		}
	}
	// 左
	if (_inputState->GetData(DIR::LEFT))
	{
		_LRflag = true;
		if (!_jumpFancFlag)
		{
			animation = AnimationCache::getInstance()->getAnimation("run");
			animeAct = RepeatForever::create(Animate::create(animation));
		}
		if (Colision()(*this, { -_size.width / 2 - speed, -_size.height / 2 })
		 && Colision()(*this, { -_size.width / 2 - speed, _size.height / 2 }))
		{
			action =  MoveBy::create(0, Vec2(-speed, 0));
			action->setTag(intCast(Tag::ACT));
		}
	}

	// しゃがみ予定
	if (_inputState->GetData(DIR::DOWN))
	{
		if (Colision()(*this, { -_size.width / 2, -_size.height / 2 - speed })
		 && Colision()(*this, { _size.width / 2, -_size.height / 2 - speed }))
		{
			this->setPosition(this->getPosition().x, this->getPosition().y - speed);
		}	
	}
	
	// 待機
	if (animation == nullptr)
	{
		if (!_jumpFancFlag)
		{
			animation = AnimationCache::getInstance()->getAnimation("idle");
			animeAct = RepeatForever::create(Animate::create(animation));
		}
	}

	// ｱﾆﾒｰｼｮﾝ
	if (animation != nullptr)
	{
		animeAct->setTag(intCast(Tag::ANIM));
		if (_oldanim != animation)
		{
			this->stopActionByTag(intCast(Tag::ANIM));
			this->runAction(animeAct);
		}
	}
	// 描画左右反転
	if (_LRflag != _oldLRflag)
	{
		this->runAction(FlipX::create(_LRflag));
	}
	// ｱｸｼｮﾝ
	if (action != nullptr)
	{
		this->stopActionByTag(intCast(Tag::ACT));
		this->runAction(action);
	}
	// ｼﾞｬﾝﾌﾟ
	if (jumpAct != nullptr)
	{
		if (_jumpFlag)
		{
			this->runAction(jumpAct);
			_jumpFlag = false;
		}
	}

	// oldを設定
	_oldLRflag = _LRflag;
	_oldanim = animation;
}