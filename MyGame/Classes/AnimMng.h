#pragma once
#include <cocos2d.h>
#include <input/OPRT_state.h>
#include <memory>

#define lpAnimMng AnimMng::GetInstance()
#define intCast(tag) static_cast<int>(tag)

enum class Tag
{
	ANIM,		// ｱﾆﾒｰｼｮﾝ
	ACT,		// ｱｸｼｮﾝ(1ﾌﾚｰﾑ毎に動かすもの)
	TRG_ACT		// ｱｸｼｮﾝ(その時だけ動かすもの)
};

class AnimMng
{
public:
	static AnimMng & GetInstance(void)
	{
		return *s_Instance;
	}	
	~AnimMng();

	// ｱﾆﾒｰｼｮﾝの作成(引数:: 誰が, keyの名前, 画像の枚数, ｱﾆﾒｰｼｮﾝの時間)
	bool AnimCreate(const std::string type, const std::string key, int num, float time); 
	void runAnim(cocos2d::Sprite& sp, Animation& anim, int repeatNum);
private:
	AnimMng();

	int _repeatNum;

	Animation* _anim;
	Animation* _oldAnim;

	static std::unique_ptr<AnimMng> s_Instance;
};

