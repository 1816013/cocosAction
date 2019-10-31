#pragma once
#include "OPRT_state.h"
struct OPRT_touch : public OPRT_state
{
	OPRT_touch(Node* sp);
	void Update()override;			// À¯Á‘€ì
	OPRT_TYPE GetType(void)override;	// ¡g‚Á‚Ä‚¢‚é“ü—ÍÀ²Ìß‚ğæ“¾(‚±‚ê‚Ítouch)
private:
	Point _startTPos;
};

