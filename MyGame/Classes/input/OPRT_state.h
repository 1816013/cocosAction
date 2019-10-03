#pragma once
#include "cocos2d.h"

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

enum class TGR_KEY	// �ضް����p
{
	NEW,	// ���݂̓���
	OLD,	// 1�ڰёO�̓���
	MAX
};

struct OPRT_state
{
	void operator()(Node* sp)
	{
		Update(sp);
	}
	virtual void Update(Node* sp) = 0;
	virtual OPRT_TYPE GetType(void) = 0;

	bool GetData(DIR dir) 
	{
		return data[static_cast<int>(dir)];
	};
	void dataInit(void)
	{
		for (int i = 0; i < static_cast<int>(DIR::MAX); i++)
		{
			data[i] = false;
		}
	}

protected:
	bool data[static_cast<int>(DIR::MAX)];
};