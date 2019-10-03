#pragma once
#include "OPRT_state.h"
struct OPRT_key : public OPRT_state
{
	void Update(Node* sp)override;
	OPRT_TYPE GetType(void)override;
};

