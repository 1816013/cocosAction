#pragma once
#include "cocos2d.h"
#include <array>

USING_NS_CC;

enum class OPRT_TYPE	// ‘€ì•û–@
{
	KEY,			// ·°ÎŞ°ÄŞ
	TOUCH,			// À¯Á
	MAX
};

enum class DIR	// •ûŒü
{
	UP,			// ã
	RIGHT,		// ‰E
	DOWN,		// ‰º
	LEFT,		// ¶
	MAX			
};

enum class KEY_MODE	// ÄØ¶Ş°”»’è—p
{
	NEW,	// Œ»İ‚Ì“ü—Í
	TRG,	// ÄØ¶Ş°“ü—Í
	MAX
};

using keyPair = std::pair<bool, bool>;

struct OPRT_state
{
	OPRT_state();
	virtual void Update() = 0;
	virtual OPRT_TYPE GetType(void) = 0;
	virtual void SetTrg(DIR dir, KEY_MODE trg) = 0;			// ÄØ¶Ş°‚Ìİ’è
	keyPair GetInput(DIR dir)
	{
		return data[static_cast<int>(dir)];
	};
	DIR GetDIR(void)
	{
		return dirData;
	}
protected:
	//bool data[static_cast<int>(DIR::MAX)];
	std::array<keyPair, static_cast<int>(DIR::MAX)>data;
	DIR dirData;
	//std::array<std::pair<DIR, TRG_KEY>, static_cast<int>(DIR::MAX)>data;
};

DIR begin(DIR);
DIR end(DIR);
DIR operator*(DIR key);
DIR operator++(DIR & key);