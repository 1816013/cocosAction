#pragma once
#include "OPRT_state.h"
struct OPRT_key : public OPRT_state
{
	OPRT_key(Node* sp);
	void Update()override;	// ｷｰの追加処理@現在使用していない
	OPRT_TYPE GetType(void)override;	// ｷｰ
};

