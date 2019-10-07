#pragma once
#include "OPRT_state.h"
struct OPRT_key : public OPRT_state
{
	OPRT_key();
	void Update(Node* sp)override;
	OPRT_TYPE GetType(void)override;
};

