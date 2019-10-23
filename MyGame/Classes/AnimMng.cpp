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

	animation->setDelayPerUnit(time); // ±ÆÒ°¼®Ý‚ÌŠúŠÔ
	animation->setRestoreOriginalFrame(true);	// ±ÆÒ°¼®ÝI—¹Žž‚É‰‚ß‚É–ß‚é‚©

	AnimationCache::getInstance()->addAnimation(animation, key);
	return true;
}

Action* AnimMng::setAnim(Animation* anim)
{
	auto anime = RepeatForever::create(Animate::create(anim));
	return anime;
}

Action* AnimMng::setAnim(Animation* anim, int repeatCnt)
{
	auto anime = Repeat::create(Animate::create(anim), repeatCnt);
	return anime;
}
