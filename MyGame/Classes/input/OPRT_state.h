#pragma once
#include "cocos2d.h"
#include <array>

USING_NS_CC;

enum class OPRT_TYPE	// ������@
{
	KEY,			// ���ް��
	TOUCH,			// ���
	MAX
};

enum class DIR	// ����
{
	UP,			// ��
	RIGHT,		// �E
	DOWN,		// ��
	LEFT,		// ��
	MAX			
};

enum class TRG_KEY	// �ضް����p
{
	NEW,	// ���݂̓���
	TRG,	// �ضް����
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