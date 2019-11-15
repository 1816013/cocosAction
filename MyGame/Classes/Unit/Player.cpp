#include "Player.h"
#include "AnimMng.h"
#include <input/OPRT_key.h>
#include <input/OPRT_touch.h>
#include <Colision.h>
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
#else
	_inputState.reset(new OPRT_touch(this));
	//_inputState = std::make_unique<OPRT_touch>();
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

// ｱﾆﾒｰｼｮﾝ設定
	lpAnimMng.AnimCreate("player", "idle", 4, 0.1f);	// 待機	
	lpAnimMng.AnimCreate("player", "run", 10, 0.1f);	// 走る
	lpAnimMng.AnimCreate("player", "jump", 6, 0.1f);		// ｼﾞｬﾝﾌﾟ
	lpAnimMng.AnimCreate("player", "duck", 1, 0.1f);	// しゃがみ


	// ﾌﾟﾚｲﾔｰ初期設定
	this->Sprite::createWithSpriteFrameName("player-idle-1.png");	// ﾌﾟﾚｲﾔｰの初期画像
	auto visibleSize = Director::getInstance()->getVisibleSize();		// ｳｲﾝﾄﾞｳｻｲｽﾞ	
	_pos = Vec2(visibleSize.width / 2, visibleSize.height / 2 + 200);	// ﾌﾟﾚｲﾔｰ初期位置
	_size = Size(60, 120);
	this->setPosition(_pos);
	this->setContentSize(_size);

	//auto speed = 5;					// ﾌﾟﾚｲﾔｰのｽﾋﾟｰﾄﾞ
	//SpeedTbl = { Vec2(0, 0),			// 何もしていない
	//			 Vec2(0, speed),		// 上
	//			 Vec2(speed, 0),		// 右
	//			 Vec2(0, -speed),		// 下
	//			 Vec2(-speed, 0) };	 	// 左

	auto setOffsetTbl = [](Sprite& sp)
	{
		auto size = sp.getContentSize();
		size = size / 2;
		DIRArrayPair offsetTbl = {
		std::make_pair(Size(0, 0),Size(0, 0)),											// 何もしていない
		std::make_pair(Size(-size.width, size.height),Size(size.width, size.height)),		// 左上, 右上 ※ 上側
		std::make_pair(Size(size.width, size.height),Size(size.width, -size.height)),		// 右上, 右下 ※ 右側
		std::make_pair(Size(-size.width, -size.height),Size(size.width, -size.height)),		// 左下, 右下 ※ 下側
		std::make_pair(Size(-size.width, size.height),Size(-size.width, -size.height)),	// 左上, 左下 ※ 左側
		};
		return offsetTbl;
	};
	_offsetTbl = setOffsetTbl(*this);

	_jumpFancFlag = false;
	
	_actMng = std::make_shared<ActionMng>();

	// 左移動
	{
		actModule module;
		module.actID = eAct::run;
		module.speed = Vec2(-5, 0);
		module.colSize = { Size(-_size.width / 2, _size.height / 2), Size(-_size.width / 2, -_size.height / 2) };
		module.keyCode = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
		module.keyMode = TRG_STATE::NOW;
		_actMng->AddActModule("左移動", module);
	}



	this->scheduleUpdate();
	return true;
}

void Player::update(float delta)
{
	// ﾄﾘｶﾞｰｷｰ用※ 1ﾌﾚｰﾑごとにｷｰﾌﾗｸﾞをfalseにする
	_inputState->update();
	_actMng->update();
	_pos = this->getPosition();
	
	// ﾃﾞﾊﾞｯｸﾞ用 ※
	// ﾌﾟﾚｲﾔｰが埋まっていたら上に一応上げる処理@ｼﾞｬﾝﾌﾟ次第で削除するかも※
	auto debugUp = [this]()
	{

		auto directer = Director::getInstance();
		auto map = (TMXTiledMap*)directer->getRunningScene()->getChildByName("backLayer")->getChildByName("mapData");
		TMXLayer* colLayer = map->getLayer("layer");
		auto tileSize = Size(colLayer->getMapTileSize().width, colLayer->getMapTileSize().height);
		auto mapTile = Size(map->getMapSize().width, map->getMapSize().height);
		Vec2 pID;
		pID = { _pos.x / tileSize.width,
				mapTile.height - ((_pos.y - _size.height / 2) / tileSize.height) };	// ﾌﾟﾚｲﾔｰ座標のID	
		if (pID.x < mapTile.width && pID.y < mapTile.height && pID.x > 0 && pID.y > 0)
		{
			if (colLayer->getTileGIDAt({ pID.x, pID.y }) != 0)
			{
				this->setPosition(_pos.x, _pos.y + (_pos.y - ((mapTile.height - pID.y + 1) *  tileSize.height)));
			}
		}
		Vec2 pNextID = { _pos.x / tileSize.width,
						 mapTile.height - ((_pos.y - _size.height) / tileSize.height) };	// ﾌﾟﾚｲﾔｰ座標のID
		if (pNextID.y < 0)
		{
			this->setPosition(this->getPosition().x, this->getPosition().y - 10);
			if (_inputState->GetInput(TRG_STATE::NOW, DIR::RIGHT))
			{
				this->setPosition(this->getPosition().x + 5, this->getPosition().y);
			}
			if (_inputState->GetInput(TRG_STATE::NOW, DIR::LEFT))
			{
				this->setPosition(this->getPosition().x - 5, this->getPosition().y);
			}
		}
	};
	//debugUp();
	//※


	// ｱｸｼｮﾝとｱﾆﾒｰｼｮﾝ
	// 移動
	//Gravity(*this);	// 重力
	DIR dir = _inputState->GetDIR();
	if (_inputState->GetInput(TRG_STATE::NOW).first)
	{

		if (_inputState->GetInput(TRG_STATE::NOW).second == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			_speed = { -5, 0 };
			_colSize[0] = { Size(-_size.width / 2, _size.height / 2) };
			_colSize[1] = { Size(-_size.width / 2, -_size.height / 2) };
		}
		if (_inputState->GetInput(TRG_STATE::NOW).second == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			_speed = { 5, 0 };
			_colSize[0] = { Size(_size.width / 2, _size.height / 2) };
			_colSize[1] = { Size(_size.width / 2, -_size.height / 2) };
		}

		if (_inputState->GetInput(TRG_STATE::NOW).second == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW
			|| _inputState->GetInput(TRG_STATE::NOW).second == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			//MoveLR(*this);		// 移動
			ChangeLR(*this, dir);	// 左右切り替え		
		}
	}
	// ｱﾆﾒｰｼｮﾝ
	auto anim = AnimationCache::getInstance()->getAnimation("idle");	// repeatNumの設定をSetAnimで設定しているため先読み必須@変更予定
	lpAnimMng.runAnim(*this, *anim, _repeatNum);

}

void Player::MoveLR(Sprite & sp)
{
	if (!Colision()(sp, _speed + _colSize[0])
		|| !Colision()(sp, _speed + _colSize[1]))
	{
		return;
	}
	sp.setPositionX(sp.getPositionX() + _speed.x);
	/*auto action = MoveBy::create(0, SpeedTbl[static_cast<int>(dir)]);
	action->setTag(intCast(Tag::ACT));
	sp.runAction(action);*/
}

void Player::Jump(Sprite & sp, DIR dir)
{
	auto callback = CallFunc::create([this]()
	{
		_jumpFancFlag = false;
	});
	if (!_jumpFancFlag)
	{
		_jumpFancFlag = true;
		auto jumpAct = Sequence::create(JumpBy::create(1.0f, { 0,0 }, 200, 1), callback, nullptr);
		jumpAct->setTag(intCast(Tag::TRG_ACT));
		this->runAction(jumpAct);
	}
}

void Player::Gravity(Sprite & sp)
{
	Vec2 gravity = { 0, -10 };
	if (Colision()(*this, gravity + Vec2{ 0, -_size.height / 2 })						// 足元の中心
		&& Colision()(*this, gravity + Vec2{ -_size.width / 2, -_size.height / 2 })		// 足元の左
		&& Colision()(*this, gravity + Vec2{ _size.width / 2, -_size.height / 2 }))		// 足元の右
	{
		if (!_jumpFancFlag)
		{
			sp.setPosition(sp.getPosition() + gravity);
		}
	}
}

void Player::ChangeLR(Sprite & sp, DIR dir)
{
	// 描画左右反転
	bool flagLR;
	if (_inputState->GetInput(TRG_STATE::NOW).second == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		flagLR = false;
	}
	else
	{
		flagLR = true;
	}
	this->runAction(FlipX::create(flagLR));

}

Animation* Player::SetAnim(DIR dir)
{
	Animation* anim = nullptr;
	_repeatNum = 0;
	if (dir == DIR::UP)
	{
		anim = AnimationCache::getInstance()->getAnimation("jump");
		_repeatNum = 1;
	}
	if (!_jumpFancFlag)
	{
		if (anim != AnimationCache::getInstance()->getAnimation("jump"))
		{
			if (dir == DIR::LEFT || dir == DIR::RIGHT)
			{
				anim = AnimationCache::getInstance()->getAnimation("run");
			}
			else if (anim == nullptr)
			{
				anim = AnimationCache::getInstance()->getAnimation("idle");
			}
		}
	}
	return anim;
}