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

#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include <Unit/Player.h>
#include <input/OPRT_key.h>
#include "EffectMng.h"
#include "SoundMng.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

GameScene::~GameScene()
{
	lpSoundMng.ckEnd();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
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

	// ﾚｲﾔｰ作成
	zorderUI = static_cast<int>(Zorder_ID::UI);
	zorderBack = static_cast<int>(Zorder_ID::BACK);
	zorderChar = static_cast<int>(Zorder_ID::CHAR);
	zorderFlont = static_cast<int>(Zorder_ID::FLONT);

	auto uiBglayer = Layer::create();
	uiBglayer->setName("uiLayer");
	auto charBglayer = Layer::create();
	charBglayer->setName("charLayer");
	auto flontBglayer = Layer::create();
	flontBglayer->setName("flontLayer");
	auto backBglayer = Layer::create();
	backBglayer->setName("backLayer");

	// ｽﾌﾟﾗｲﾄ作成

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));

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
   // this->addChild(menu, zorderUI);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("1816013 kimura riku", "fonts/Marker Felt.ttf", 24);
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
       // this->addChild(label, zorderUI);
    }

	auto pos = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

	// 背景
	auto backS1 = Sprite::create("image/Environment/middleground2.png");
	backS1->setPosition(backS1->getContentSize().width / 2, backS1->getContentSize().height / 2);
	auto backS2 = Sprite::create("image/Environment/middleground2.png");
	backS2->setPosition(backS2->getContentSize().width / 2 + backS2->getContentSize().width, backS2->getContentSize().height / 2);

	// ﾏｯﾌﾟ
	auto mapS = TMXTiledMap::create("map2.tmx");
	mapS->setName("mapData");
	mapS->setPosition({ -16, 0 });
	auto footingL = mapS->getLayer("footing");
	footingL->setGlobalZOrder(zorderBack);
	
	// ｹﾞｰﾄ
	auto gateS = Sprite::create("image/Environment/Props/gate-01.png");
	gateS->setPosition(gateS->getContentSize().width / 2, gateS->getContentSize().height / 2 + 48);
	
	// ﾌﾟﾚｲﾔｰ作成
	auto player = Player::createSprite();
	
	// ｽﾌﾟﾗｲﾄをﾚｲﾔｰにぶら下げる
	uiBglayer->addChild(menu, 0);
	uiBglayer->addChild(label, 0);

	charBglayer->addChild(player, 0);

	backBglayer->addChild(backS1, 0);
	backBglayer->addChild(backS2, 0);

	flontBglayer->addChild(mapS, 0);
	flontBglayer->addChild(gateS, 0);

	// エフェクト
	effecMng.reset(efk::EffectManager::create(visibleSize));
	effecMng.get()->end()
	lpEffectMng.AddEffect("Laser01.efk", 13.0f, effecMng.get());

	flontBglayer->addChild(lpEffectMng.GetEmitter("Laser01.efk"),0);

	// ｼｰﾝにぶら下げる
	this->addChild(uiBglayer, zorderUI);
	this->addChild(backBglayer, zorderBack);
	this->addChild(charBglayer, zorderChar);
	this->addChild(flontBglayer, zorderFlont);

	// ｻｳﾝﾄﾞ
	lpSoundMng.Init();
	lpSoundMng.AddSound("sound.ckb", "shot", SOUND_TYPE::SE);
	lpSoundMng.AddSound("sound.ckb", "bgm", SOUND_TYPE::BGM);

	this->scheduleUpdate();

    return true;
	
}

void GameScene::update(float delta)
{	
	(*effecMng).update();
	//lpSoundMng.Update();
	if (count == 0)
	{
		lpSoundMng.PlayBySoundName("bgm");
	}
		
	count++;
}


void GameScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();


    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void GameScene::visit(cocos2d::Renderer * renderer, const cocos2d::Mat4 & parentTransform, uint32_t parentFlags)
{
	(*effecMng).begin(renderer, _globalZOrder);
	cocos2d::Scene::visit(renderer, parentTransform, parentFlags);
	(*effecMng).end(renderer, _globalZOrder);
}

