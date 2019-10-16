#include "AnimMng.h"

std::unique_ptr<AnimMng>AnimMng::s_Instance(new AnimMng);


AnimMng::AnimMng()
{
}

AnimMng::~AnimMng()
{
}

bool AnimMng::AnimCreate(const std::string key, int cnt, float time)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(key + ".plist");
	auto animation = Animation::create();
	for (int i = 1; i <= cnt; i++)
	{
		auto str = __String::createWithFormat((key + "-%i.png").c_str(), i);
		SpriteFrame *sprite = SpriteFrameCache::getInstance()->getSpriteFrameByName(str->getCString());
		animation->addSpriteFrame(sprite);
	}

	animation->setDelayPerUnit(time); // ｱﾆﾒｰｼｮﾝの期間
	animation->setRestoreOriginalFrame(true);	// ｱﾆﾒｰｼｮﾝ終了時に初めに戻るか

	AnimationCache::getInstance()->addAnimation(animation, key);
	return true;
}
