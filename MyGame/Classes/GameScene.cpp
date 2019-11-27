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

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
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
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Game Scene", "fonts/Marker Felt.ttf", 24);
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
        this->addChild(label, 5);
    }

	auto pos = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

	ZorderBack = static_cast<int>(Zorder_ID::BACK);
	ZorderChar = static_cast<int>(Zorder_ID::CHAR);
	ZorderFlont = static_cast<int>(Zorder_ID::FLONT);
	// Ú²Ô°ì¬
	//auto bglayer = Layer::create();
	
	auto charbglayer = Layer::create();
	charbglayer->setName("charLayer");
	auto flontbglayer = Layer::create();
	flontbglayer->setName("flontLayer");
	auto backbglayer = Layer::create();
	backbglayer->setName("backLayer");

	// ½Ìß×²Äì¬
	// ”wŒi
	auto backS1 = Sprite::create("image/Environment/middleground2.png");
	backS1->setPosition(backS1->getContentSize().width / 2, backS1->getContentSize().height / 2);
	auto backS2 = Sprite::create("image/Environment/middleground2.png");
	backS2->setPosition(backS2->getContentSize().width / 2 + backS2->getContentSize().width, backS2->getContentSize().height / 2);

	// Ï¯Ìß
	auto mapS = TMXTiledMap::create("map.tmx");
	mapS->setName("mapData");
	//mapS->setPosition({ -16, 0 });
	//auto waterL = mapS->getLayer("water");	// …
	//waterL->setGlobalZOrder(ZorderFlont);
	//auto plantL = mapS->getLayer("plant");	// A•¨
	//plantL->setGlobalZOrder(ZorderFlont);
	//auto caveL = mapS->getLayer("cave1");
	//caveL->setGlobalZOrder(ZorderFlont);
	

	// ¹Þ°Ä
	/*auto gateS = Sprite::create("image/Environment/Props/gate-01.png");
	gateS->setPosition(gateS->getContentSize().width / 2, gateS->getContentSize().height / 2 + 48);*/
	
	// ÌßÚ²Ô°
	auto player = Player::createSprite();

	// ½Ìß×²Ä‚ðÚ²Ô°‚É‚Ô‚ç‰º‚°‚é
	charbglayer->addChild(player, 0);

	backbglayer->addChild(backS1, 0);
	backbglayer->addChild(backS2, 0);
	backbglayer->addChild(mapS, 0);

	//flontbglayer->addChild(gateS, 0);
	effecMng.reset(efk::EffectManager::create(visibleSize));
	//(*effecMng).create(visibleSize);
	auto effect = efk::Effect::create("Laser01.efk", 13.0f);
	auto emitter = efk::EffectEmitter::create(effecMng.get());
	emitter->setEffect(effect);
	emitter->setPlayOnEnter(true);

	emitter->setRotation3D(cocos2d::Vec3(0, 90, 0));
	emitter->setPosition(Vec2(300, 120));

	flontbglayer->addChild(emitter,0);

	// ¼°Ý‚É‚Ô‚ç‰º‚°‚é
	this->addChild(backbglayer, ZorderBack);
	this->addChild(charbglayer, ZorderChar);
	this->addChild(flontbglayer, ZorderFlont);

	this->scheduleUpdate();
    return true;
	
}

void GameScene::update(float delta)
{	
	(*effecMng).update();
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

