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
	CENTER,		// ����
	UP,			// ��
	RIGHT,		// �E
	DOWN,		// ��
	LEFT,		// ��
	MAX			
};

enum class TGR_KEY	// �ضް����p
{
	NEW,	// ���݂̓���
	OLD,	// 1�ڰёO�̓���
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