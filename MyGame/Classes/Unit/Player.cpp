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
	_actMng = std::make_shared<ActionMng>();
#else
	_inputState.reset(new OPRT_touch(this));
	_actMng.reset(new ActionMng());
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
	_jumpSpeed = 0.0f;

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
		module.keyCode = EventKeyboard::KeyCode::KEY_UP_ARROW;
		module.keyMode = TRG_STATE::NOW;
		module.keyTiming = Timing::ON_MOM;
		_actMng->AddActModule("ｼﾞｬﾝﾌﾟ", module);
	}
	// ｼﾞｬﾝﾌﾟ中
	{
		actModule module;
		module.actID = ACT_STATE::JUMPING;
		module.speed = Vec2(0, _jumpSpeed);
		module.colSize = { Size(30, 45), Size(-30, 40) };
		_actMng->AddActModule("ｼﾞｬﾝﾌﾟ中", module);
	}
	// 落下
	{
		actModule module;
		module.actID = ACT_STATE::FALL;
		module.speed = Vec2(0, -5);
		module.colSize = { Size(30, -60), Size(-30, -60) };
		_actMng->AddActModule("落下", module);
	}
	// 落下中
	{
		actModule module;
		module.actID = ACT_STATE::FALLING;
		module.speed = Vec2(0, -5);
		module.colSize = { Size(30, -60), Size(-30, -60) };
		_actMng->AddActModule("落下", module);
	}

	this->scheduleUpdate();
	return true;
}

void Player::update(float delta)
{
	_inputState->update();
	_actMng->update(*this);
	
	// ﾃﾞﾊﾞｯｸﾞ用 ※
	// ﾌﾟﾚｲﾔｰが埋まっていたら上に一応上げる処理@ｼﾞｬﾝﾌﾟ次第で削除するかも※
	auto debugUp = [this]()
	{
		_pos = this->getPosition();
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
	auto anim = AnimationCache::getInstance()->getAnimation("idle");	// repeatNumの設定をSetAnimで設定しているため先読み必須@変更予定
	lpAnimMng.runAnim(*this, *anim, _repeatNum);

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

void Player::ChangeLR(Sprite & sp, DIR dir)
{
	// 描画左右反転
	bool flagLR;
	if (_inputState->GetInput(TRG_STATE::NOW, cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW))
	{
		flagLR = false;
	}
	else
	{
		flagLR = true;
	}
	this->runAction(FlipX::create(flagLR));

}

void Player::JumpSpeed(float speed)
{
	_jumpSpeed = speed;
}

float Player::JumpSpeed(void)
{
	return _jumpSpeed;
}

Animation* Player::SetAnim(DIR dir)
{
	auto animCache = AnimationCache::getInstance();
	Animation* anim = nullptr;
	_repeatNum = 0;
	if (dir == DIR::UP)
	{
		anim = animCache->getAnimation("jump");
		_repeatNum = 1;
	}
	if (!_jumpFancFlag)
	{
		if (anim != animCache->getAnimation("jump"))
		{
			if (dir == DIR::LEFT || dir == DIR::RIGHT)
			{
				anim = animCache->getAnimation("run");
			}
			else if (anim == nullptr)
			{
				anim = animCache->getAnimation("idle");
			}
		}
	}
	return anim;
}