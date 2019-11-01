#pragma once
#include "OPRT_state.h"
struct OPRT_key : public OPRT_state
{
	OPRT_key(Node* sp);
	void Update()override;				// ·°‚Ì’Ç‰Áˆ—(ÄØ¶Ş°ˆ—)
	OPRT_TYPE GetType(void)override;	// ¡g‚Á‚Ä‚¢‚é“ü—ÍÀ²Ìß‚ğæ“¾(‚±‚ê‚Íkey)
	void SetTrg(DIR dir, KEY_MODE trg);			// ÄØ¶Ş°‚Ìİ’è
};

