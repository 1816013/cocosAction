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

	// ��Ұ��݂̍쐬(����:: �N��, key�̖��O, �摜�̖���, ��Ұ��݂̎���)
	bool AnimCreate(const std::string type, const std::string key, int num, float time); 

	/*Action* setAnim(Animation* anim);							
	Action* setAnim(Animation* anim, int repeatCnt);*/
private:
	AnimMng();

	static std::unique_ptr<AnimMng> s_Instance;
};

