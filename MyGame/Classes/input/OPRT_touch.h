#pragma once
#include "OPRT_state.h"
struct OPRT_touch : public OPRT_state
{
	OPRT_touch(Node* sp);
	void Update()override;			// �������
	OPRT_TYPE GetType(void)override;	// ���g���Ă���������߂��擾(�����touch)
private:
	Point _startTPos;
};

