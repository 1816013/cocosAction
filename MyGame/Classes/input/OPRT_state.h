#pragma once
#include "cocos2d.h"
#include <array>

USING_NS_CC;

enum class OPRT_TYPE	// 操作方法
{
	KEY,			// ｷｰﾎﾞｰﾄﾞ
	TOUCH,			// ﾀｯﾁ
	MAX
};

enum class DIR	// 方向
{
	UP,			// 上
	RIGHT,		// 右
	DOWN,		// 下
	LEFT,		// 左
	MAX			
};

enum class TRG_KEY	// ﾄﾘｶﾞｰ判定用
{
	NEW,	// 現在の入力
	TRG,	// ﾄﾘｶﾞｰ入力
	MAX
};

using keyPair = std::pair<bool, TRG_KEY>;

struct OPRT_state
{
	OPRT_state();
	virtual void Update() = 0;
	virtual OPRT_TYPE GetType(void) = 0;
	keyPair GetData(DIR dir)
	{
		return data[static_cast<int>(dir)];
	};
protected:
	//bool data[static_cast<int>(DIR::MAX)];
	std::array<keyPair, static_cast<int>(DIR::MAX)>data;
};

DIR begin(DIR);
DIR end(DIR);
DIR operator*(DIR key);
DIR operator++(DIR & key);