#pragma once
#include "OPRT_state.h"
struct OPRT_key : public OPRT_state
{
	OPRT_key(Node* sp);
	void Update()override;				// ���̒ǉ�����(�ضް����)
	OPRT_TYPE GetType(void)override;	// ���g���Ă���������߂��擾(�����key)
	void SetTrg(DIR dir, KEY_MODE trg);			// �ضް�̐ݒ�
};

