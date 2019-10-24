#pragma once
#include <cocos2d.h>
#include <memory>

USING_NS_CC;

#define lpAnimMng AnimMng::GetInstance()

class AnimMng
{
public:
	static AnimMng & GetInstance(void)
	{
		return *s_Instance;
	}	
	~AnimMng();

	bool AnimCreate(const std::string type, const std::string key, int cnt, float time);	// ±∆“∞ºÆ›ÇÃçÏê¨
	/*Action* setAnim(Animation* anim);							
	Action* setAnim(Animation* anim, int repeatCnt);*/
private:
	AnimMng();

	



	static std::unique_ptr<AnimMng> s_Instance;
};

