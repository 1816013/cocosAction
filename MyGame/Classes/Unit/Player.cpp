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
	// ���ײĸ׽�̏�����@init�����삵�����ߕK�v
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

// ��Ұ��ݐݒ�
	lpAnimMng.AnimCreate("player", "idle", 4, 0.1f);	// �ҋ@	
	lpAnimMng.AnimCreate("player", "run", 10, 0.1f);	// ����
	lpAnimMng.AnimCreate("player", "jump", 6, 0.1f);		// �ެ���
	lpAnimMng.AnimCreate("player", "duck", 1, 0.1f);	// ���Ⴊ��


	// ��ڲ԰�����ݒ�
	this->Sprite::createWithSpriteFrameName("player-idle-1.png");	// ��ڲ԰�̏����摜
	auto visibleSize = Director::getInstance()->getVisibleSize();		// ����޳����	
	_pos = Vec2(visibleSize.width / 2, visibleSize.height / 2 + 200);	// ��ڲ԰�����ʒu
	_size = Size(60, 120);
	this->setPosition(_pos);
	this->setContentSize(_size);

	//auto speed = 5;					// ��ڲ԰�̽�߰��
	//SpeedTbl = { Vec2(0, 0),			// �������Ă��Ȃ�
	//			 Vec2(0, speed),		// ��
	//			 Vec2(speed, 0),		// �E
	//			 Vec2(0, -speed),		// ��
	//			 Vec2(-speed, 0) };	 	// ��

	auto setOffsetTbl = [](Sprite& sp)
	{
		auto size = sp.getContentSize();
		size = size / 2;
		DIRArrayPair offsetTbl = {
		std::make_pair(Size(0, 0),Size(0, 0)),											// �������Ă��Ȃ�
		std::make_pair(Size(-size.width, size.height),Size(size.width, size.height)),		// ����, �E�� �� �㑤
		std::make_pair(Size(size.width, size.height),Size(size.width, -size.height)),		// �E��, �E�� �� �E��
		std::make_pair(Size(-size.width, -size.height),Size(size.width, -size.height)),		// ����, �E�� �� ����
		std::make_pair(Size(-size.width, size.height),Size(-size.width, -size.height)),	// ����, ���� �� ����
		};
		return offsetTbl;
	};
	_offsetTbl = setOffsetTbl(*this);

	_jumpFancFlag = false;
	
	_actMng = std::make_shared<ActionMng>();

	// ���ړ�
	{
		actModule module;
		module.actID = eAct::run;
		module.speed = Vec2(-5, 0);
		module.colSize = { Size(-_size.width / 2, _size.height / 2), Size(-_size.width / 2, -_size.height / 2) };
		module.keyCode = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
		module.keyMode = TRG_STATE::NOW;
		_actMng->AddActModule("���ړ�", module);
	}



	this->scheduleUpdate();
	return true;
}

void Player::update(float delta)
{
	// �ضް���p�� 1�ڰт��Ƃɷ��׸ނ�false�ɂ���
	_inputState->update();
	_actMng->update();
	_pos = this->getPosition();
	
	// ���ޯ�ޗp ��
	// ��ڲ԰�����܂��Ă������Ɉꉞ�グ�鏈��@�ެ��ߎ���ō폜���邩����
	auto debugUp = [this]()
	{

		auto directer = Director::getInstance();
		auto map = (TMXTiledMap*)directer->getRunningScene()->getChildByName("backLayer")->getChildByName("mapData");
		TMXLayer* colLayer = map->getLayer("layer");
		auto tileSize = Size(colLayer->getMapTileSize().width, colLayer->getMapTileSize().height);
		auto mapTile = Size(map->getMapSize().width, map->getMapSize().height);
		Vec2 pID;
		pID = { _pos.x / tileSize.width,
				mapTile.height - ((_pos.y - _size.height / 2) / tileSize.height) };	// ��ڲ԰���W��ID	
		if (pID.x < mapTile.width && pID.y < mapTile.height && pID.x > 0 && pID.y > 0)
		{
			if (colLayer->getTileGIDAt({ pID.x, pID.y }) != 0)
			{
				this->setPosition(_pos.x, _pos.y + (_pos.y - ((mapTile.height - pID.y + 1) *  tileSize.height)));
			}
		}
		Vec2 pNextID = { _pos.x / tileSize.width,
						 mapTile.height - ((_pos.y - _size.height) / tileSize.height) };	// ��ڲ԰���W��ID
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
	//��


	// ����݂Ʊ�Ұ���
	// �ړ�
	//Gravity(*this);	// �d��
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
			//MoveLR(*this);		// �ړ�
			ChangeLR(*this, dir);	// ���E�؂�ւ�		
		}
	}
	// ��Ұ���
	auto anim = AnimationCache::getInstance()->getAnimation("idle");	// repeatNum�̐ݒ��SetAnim�Őݒ肵�Ă��邽�ߐ�ǂݕK�{@�ύX�\��
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
	if (Colision()(*this, gravity + Vec2{ 0, -_size.height / 2 })						// �����̒��S
		&& Colision()(*this, gravity + Vec2{ -_size.width / 2, -_size.height / 2 })		// �����̍�
		&& Colision()(*this, gravity + Vec2{ _size.width / 2, -_size.height / 2 }))		// �����̉E
	{
		if (!_jumpFancFlag)
		{
			sp.setPosition(sp.getPosition() + gravity);
		}
	}
}

void Player::ChangeLR(Sprite & sp, DIR dir)
{
	// �`�捶�E���]
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