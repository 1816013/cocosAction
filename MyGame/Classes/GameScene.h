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

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <vector>
#include <memory>
#include <Unit/Obj.h>
#include "Effekseer/Effekseer.h"
#include <ck/bank.h>
#include <ck/sound.h>



enum class ActionType
{
	IDLE,
	RUN
};

enum class Zorder_ID
{
	BACK = 0,
	CHAR = 50,
	FLONT = 100,
	MAX = 1000000
};

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
	~GameScene();
	void update(float delta)override;

    virtual bool init();
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	virtual void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags) override;
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
	OPRT_state* state;
private:

	CkBank* bank;
	CkSound* sound;

	std::unique_ptr<efk::EffectManager>effecMng;

	efk::EffectEmitter* emitter2;
	int ZorderBack;		// ˆê”ÔŒã‚ë‚Ìzorder
	int ZorderChar;		// ·¬×‚Ìzorder
	int ZorderFlont;	// ˆê”Ô‘O‚Ìzorder
	int count;
};

#endif // __HELLOWORLD_SCENE_H__
