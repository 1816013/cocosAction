/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <input/OPRT_key.h>
#include <input/OPRT_touch.h>
//#include <Unit/Player.h>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    //// add "HelloWorld" splash screen"
	//sprite = Sprite::create("HelloWorld.png");
	//if (sprite == nullptr)
	//{
	//	problemLoading("'HelloWorld.png'");
	//}
	//else
	//{
	//	// position the sprite on the center of the screen
	//	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//	// add the sprite as a child to this layer
	//	this->addChild(sprite, 1);
	//}

	// plist
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("player-idle.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("player-run.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("player-jump.plist");

	// プレイヤー初期設定
	player = Sprite::createWithSpriteFrameName("player-idle-1.png");
	if (player == nullptr)
	{
		problemLoading("'player_idle-1.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		player->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		player->setScale(2.0f);
		// add the sprite as a child to this layer
		this->addChild(player, 0);
	}
	
	// アニメーション設定
	// idle
	AnimCreate("player-idle-%i.png", 4, 0.1f, true, "idle");
	//auto animation = Animation::create();
	//for (int i = 1; i <= 4; i++) 
	//{
	//	auto str = __String::createWithFormat("player-idle-%i.png", i);
	//	SpriteFrame *sprite = SpriteFrameCache::getInstance()->getSpriteFrameByName(str->getCString());
	//	animation->addSpriteFrame(sprite);
	//}
	//animation->setDelayPerUnit(0.2f); //アニメの動く時間を設定
	//animation->setRestoreOriginalFrame(true);	// ｱﾆﾒｰｼｮﾝ終了時にｱﾆﾒｰｼｮﾝの最初に戻るかどうか
	//AnimationCache::getInstance()->addAnimation(animation, "idle");
	//auto action = Animate::create(animation);
	//auto anime = RepeatForever::create(action);
	//oldanim = animation;
	//player->runAction(anime);*/

	// run
	AnimCreate("player-run-%i.png", 10, 0.1f, true, "run");
	// jump
	
	//auto sprite = Sprite::createWithSpriteFrameName("player-jump-1.png");
	// position the sprite on the center of the screen
	//player->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	// add the sprite as a child to this layer
	//this->addChild(sprite, 0);
	// アニメーション
	AnimCreate("player-jump-%i.png", 6, 0.1f, true, "jump");
	//auto animation2 = Animation::create();
	//for (int i = 1; i <= 6; i++)
	//{
	//	auto str2 = __String::createWithFormat("player-jump-%i.png", i);
	//	SpriteFrame *sprite2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str2->getCString());
	//	animation2->addSpriteFrame(sprite2);
	//}
	//animation2->setDelayPerUnit(0.2f); //アニメの動く時間を設定
	//animation2->setRestoreOriginalFrame(true);	// ｱﾆﾒｰｼｮﾝ終了時にｱﾆﾒｰｼｮﾝの最初に戻るかどうか
	//AnimationCache::getInstance()->addAnimation(animation2, "jump");

	//objList.emplace_back(new Player());
	pos = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	LRflag = false;
	
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	_inputState = std::make_unique<OPRT_key>();
	//state = new(OPRT_key);
#else
	_inputState.reset(new OPRT_touch());
	//_inputState = std::make_unique<OPRT_touch>();
	//state = new(OPRT_touch);
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

	this->scheduleUpdate();
    return true;
	
}

void HelloWorld::update(float delta)
{
	Action* anime = nullptr;
	Action* action = nullptr;
	Action* jump;

	Animation* animation = oldanim;
	_inputState->Update(this);
	auto speed = 3;
	if (_inputState->GetData(DIR::UP))
	{
		jumpFlag = true;
		//player->setPosition(pos.x, pos.y += speed);
		animation = AnimationCache::getInstance()->getAnimation("jump");
		anime = Repeat::create(Animate::create(animation), 1);
		jump = JumpBy::create(1.0f, { 0,0 }, 50, 1);
		anime->setTag(0);
		jump->setTag(2);
		jumpTimeFlag = true;
		jumpTime = 0;
		//anime = Spawn::create(anim, jump, nullptr);
	}
	if (_inputState->GetData(DIR::RIGHT))
	{
		LRflag = false;
		animation = AnimationCache::getInstance()->getAnimation("run");
		anime = RepeatForever::create(Animate::create(animation));
		auto move = MoveBy::create(0, Vec2(1, 0));
		action = Spawn::create(FlipX::create(LRflag), move, nullptr);
		anime->setTag(0);
		action->setTag(1);	
	}
	if (_inputState->GetData(DIR::DOWN))
	{
		animation = AnimationCache::getInstance()->getAnimation("idle");
		anime = RepeatForever::create(Animate::create(animation));
		action = Spawn::create(FlipX::create(LRflag), nullptr);
		anime->setTag(0);
		action->setTag(1);
	}
	if (_inputState->GetData(DIR::LEFT))
	{
		LRflag = true;
		animation = AnimationCache::getInstance()->getAnimation("run");
		anime = RepeatForever::create(Animate::create(animation));
		auto move = MoveBy::create(0, Vec2(-1, 0));
		action = Spawn::create(FlipX::create(LRflag), move, nullptr);
		anime->setTag(0);
		action->setTag(1);
		
	}
	if (!_inputState->GetData(DIR::UP) && !_inputState->GetData(DIR::RIGHT) && !_inputState->GetData(DIR::DOWN) && !_inputState->GetData(DIR::LEFT) || _inputState->GetData(DIR::RIGHT) && _inputState->GetData(DIR::LEFT))
	{
		if (!jumpTimeFlag)
		{
			animation = AnimationCache::getInstance()->getAnimation("idle");
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
			//player->stopAllActions();
			player->stopActionByTag(0);
			player->runAction(anime);
		}
	}

	if (action != nullptr)
	{
		player->stopActionByTag(1);
		player->runAction(action);
	}
	
	if (jump != nullptr)
	{
		if (jumpFlag)
		{
			player->runAction(jump);
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
	//sprite->runAction(RepeatForever sequence);
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

bool HelloWorld::AnimCreate(const char* name, int cnt, float time, bool flag, const std::string & key)
{
	auto animation = Animation::create();
	for (int i = 1; i <= cnt; i++)
	{
		auto str = __String::createWithFormat(name, i);
		SpriteFrame *sprite = SpriteFrameCache::getInstance()->getSpriteFrameByName(str->getCString());
		animation->addSpriteFrame(sprite);
	}

	animation->setDelayPerUnit(time); //アニメの動く時間を設定
	animation->setRestoreOriginalFrame(flag);	// ｱﾆﾒｰｼｮﾝ終了時にｱﾆﾒｰｼｮﾝの最初に戻るかどうか

	AnimationCache::getInstance()->addAnimation(animation, key);
	return true;
}
