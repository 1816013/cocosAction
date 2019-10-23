#pragma once
#include "OPRT_state.h"
struct OPRT_key : public OPRT_state
{
	OPRT_key(Node* sp);
	void Update()override;	// ·°‚Ì’Ç‰Áˆ—@Œ»İg—p‚µ‚Ä‚¢‚È‚¢
	OPRT_TYPE GetType(void)override;	// ·°
};

