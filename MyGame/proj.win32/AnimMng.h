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
private:
	AnimMng();

	bool AnimCreate(const char* name, int cnt, float time, bool flag, const std::string & key);



	static std::unique_ptr<AnimMng> s_Instance;
};

