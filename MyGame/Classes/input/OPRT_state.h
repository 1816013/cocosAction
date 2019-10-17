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
	CENTER,		// 中央
	UP,			// 上
	RIGHT,		// 右
	DOWN,		// 下
	LEFT,		// 左
	MAX			
};

enum class TGR_KEY	// ﾄﾘｶﾞｰ判定用
{
	NEW,	// 現在の入力
	OLD,	// 1ﾌﾚｰﾑ前の入力
	MAX
};

struct OPRT_state
{
	OPRT_state(){};
	virtual void Update() = 0;
	virtual OPRT_TYPE GetType(void) = 0;

	bool GetData(DIR dir) 
	{
		return data[static_cast<int>(dir)];
	};


protected:
	//bool data[static_cast<int>(DIR::MAX)];
	std::array<bool, static_cast<int>(DIR::MAX)>data;
};