#pragma once
#include "OPRT_state.h"
struct OPRT_touch : public OPRT_state
{
	OPRT_touch(Node* sp);
	void Update()override;			// �������
	OPRT_TYPE GetType(void)override;	// ��������
private:
	Point _startTPos;
};

