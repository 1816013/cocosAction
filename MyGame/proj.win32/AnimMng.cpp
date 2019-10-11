#include "AnimMng.h"

std::unique_ptr<AnimMng>AnimMng::s_Instance(new AnimMng);


AnimMng::AnimMng()
{
}

AnimMng::~AnimMng()
{
}

bool AnimMng::AnimCreate(const char* name, int cnt, float time, bool flag, const std::string & key)
{
	auto animation = Animation::create();
	for (int i = 1; i <= cnt; i++)
	{
		auto str = __String::createWithFormat(name, i);
		SpriteFrame *sprite = SpriteFrameCache::getInstance()->getSpriteFrameByName(str->getCString());
		animation->addSpriteFrame(sprite);
	}

	animation->setDelayPerUnit(time); //ƒAƒjƒ‚Ì“®‚­ŽžŠÔ‚ðÝ’è
	animation->setRestoreOriginalFrame(flag);	// ±ÆÒ°¼®ÝI—¹Žž‚É±ÆÒ°¼®Ý‚ÌÅ‰‚É–ß‚é‚©‚Ç‚¤‚©

	AnimationCache::getInstance()->addAnimation(animation, key);
	return true;
}
