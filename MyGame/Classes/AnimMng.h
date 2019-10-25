#pragma once
#include <cocos2d.h>
#include <memory>

#define lpAnimMng AnimMng::GetInstance()

class AnimMng
{
public:
	static AnimMng & GetInstance(void)
	{
		return *s_Instance;
	}	
	~AnimMng();

	// ±ÆÒ°¼®İ‚Ìì¬(ˆø”:: ’N‚ª, key‚Ì–¼‘O, ‰æ‘œ‚Ì–‡”, ±ÆÒ°¼®İ‚ÌŠÔ)
	bool AnimCreate(const std::string type, const std::string key, int num, float time); 

	/*Action* setAnim(Animation* anim);							
	Action* setAnim(Animation* anim, int repeatCnt);*/
private:
	AnimMng();

	static std::unique_ptr<AnimMng> s_Instance;
};

