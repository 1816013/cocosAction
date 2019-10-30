#include "AnimMng.h"

USING_NS_CC;

std::unique_ptr<AnimMng>AnimMng::s_Instance(new AnimMng);

AnimMng::AnimMng()
{
	repeatNum = 0;
}

AnimMng::~AnimMng()
{
}

// ±ÆÒ°¼®Ý‚Ìì¬
bool AnimMng::AnimCreate(const std::string type, const std::string key, int num, float time)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/"+ type + "/" + type + "-" + key + ".plist");
	auto animation = Animation::create();
	if (num == 1)
	{
		auto str = type + "-" + key + ".png";
		SpriteFrame *sprite = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		animation->addSpriteFrame(sprite);
	}
	else
	{
		for (int i = 1; i <= 20; i++)
		{
			auto str = __String::createWithFormat((type + "-" + key + "-%i.png").c_str(), i);
			SpriteFrame *sprite = SpriteFrameCache::getInstance()->getSpriteFrameByName(str->getCString());
			if (sprite == nullptr)
			{
				break;
			}
			animation->addSpriteFrame(sprite);
		}
	}

	animation->setDelayPerUnit(time); // ±ÆÒ°¼®Ý‚ÌŠúŠÔ
	animation->setRestoreOriginalFrame(true);	// ±ÆÒ°¼®ÝI—¹Žž‚É‰‚ß‚É–ß‚é‚©

	AnimationCache::getInstance()->addAnimation(animation, key);
	return true;
}

void AnimMng::SetAnim(DIR dir, bool flag)
{
	if (!flag)
	{
		_anim = nullptr;
		if (dir == DIR::LEFT || dir == DIR::RIGHT)
		{
			_anim = AnimationCache::getInstance()->getAnimation("run");
		}
		
		if (_anim == nullptr)
		{
			_anim = AnimationCache::getInstance()->getAnimation("idle");
		}
	}
}

void AnimMng::runAnim(Sprite& sp, DIR dir)
{
	if (_anim == nullptr)
	{
		return;
	}
	Action* animAct;
	if (repeatNum <= 0)
	{
		animAct = RepeatForever::create(Animate::create(_anim));
	}
	else
	{
		animAct = Repeat::create(Animate::create(_anim), repeatNum);
	}
	animAct->setTag(intCast(Tag::ANIM));
	if (_oldAnim != _anim)
	{
		sp.stopActionByTag(intCast(Tag::ANIM));
		sp.runAction(animAct);
		_oldAnim = _anim;
	}
}

//Action* AnimMng::setAnim(Animation& anim)
//{
//	auto anime = RepeatForever::create(Animate::create(&anim));
//	anime->setTag(intCast(Tag::ANIM));
//	return anime;
//}
//
//Action* AnimMng::setAnim(Animation& anim, int repeatCnt)
//{
//	auto anime = Repeat::create(Animate::create(&anim), repeatCnt);
//	anime->setTag(intCast(Tag::ANIM));
//	return anime;
//}
//
//
//void AnimMng::runAnim(Sprite & sp, Action& anim)
//{
//	if (&anim != nullptr)
//	{
//		
//		/*if (_oldanim != anim)
//		{*/
//			sp.stopActionByTag(intCast(Tag::ANIM));
//			sp.runAction(&anim);
//		//}
//	}
//}
//
