#pragma once
#include "OPRT_state.h"
struct OPRT_touch : public OPRT_state
{
	OPRT_touch(Node* sp);
	void Update()override;			// À¯Á‘€ì
	OPRT_TYPE GetType(void)override;	// “ü—ÍÀ²Ìß
private:
	Point _startTPos;
};

