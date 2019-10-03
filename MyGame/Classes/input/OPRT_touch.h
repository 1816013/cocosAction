#pragma once
#include "OPRT_state.h"
struct OPRT_touch : public OPRT_state
{
	void Update(Node* sp)override;			// À¯Á‘€ì
	OPRT_TYPE GetType(void)override;	// “ü—ÍÀ²Ìß

	bool TouchStart(EventListenerTouchOneByOne* listener);
	void TouchEnd(void);
	void TouchMove(void);
private:
	Point _startTPos;
};

