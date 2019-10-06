#include "Player.h"

Player::Player()
{
	_pos = { 250, 200 };
	Init();

}

Player::~Player()
{
}

void Player::Init(void)
{
	sprite = Sprite::create("image/Sprites/player/player-idle/player-idle-1.png");
	if (sprite == nullptr)
	{
		//problemLoading("'HelloWorld.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		sprite->setPosition(_pos.x, _pos.y);

		// add the sprite as a child to this layer
		this->addChild(sprite, 0);
	}
}

void Player::Update(bool dir)
{
}
