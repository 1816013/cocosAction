#pragma once
#include "OPRT_state.h"
struct OPRT_key : public OPRT_state
{
	OPRT_key(Node* sp);
	void Update()override;	// ���̒ǉ�����@���ݎg�p���Ă��Ȃ�
	OPRT_TYPE GetType(void)override;	// ��
};

