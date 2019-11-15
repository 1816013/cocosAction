#pragma once
#include "cocos2d.h"
#include <array>
#include <map>

USING_NS_CC;

#define intCast(tag) static_cast<int>(tag)

enum class OPRT_TYPE	// ‘€ì•û–@
{
	KEY,			// ·°ÎŞ°ÄŞ
	TOUCH,			// À¯Á
	MAX
};

enum class DIR	// •ûŒü
{
	NEUTRAL,	// ‰½‚à‚µ‚Ä‚¢‚È‚¢
	UP,			// ã
	RIGHT,		// ‰E
	DOWN,		// ‰º
	LEFT,		// ¶
	MAX			
};

enum class Timing
{
	ON,
	ON_MOM,
	OFF,
	OFFMOM
};

enum class TRG_STATE	// ÄØ¶Ş°”»’è—p
{
	NOW,	// Œ»İ‚Ì“ü—Í
	OLD,	// ÄØ¶Ş°“ü—Í
	INPUT,	//
	MAX
};

using DIR_ArrayTouch =  std::array<bool, intCast(DIR::MAX)>;
using TRG_ArrayTouch = std::array<DIR_ArrayTouch, intCast(TRG_STATE::MAX)>;

using KeyPair = std::pair<bool, cocos2d::EventKeyboard::KeyCode>;
//using DIR_ArrayKey = std::array<KeyPair, intCast(DIR::MAX)>;
using TRG_ArrayKey = std::array<KeyPair, intCast(TRG_STATE::MAX)>;

struct OPRT_state
{
	OPRT_state();
	virtual OPRT_TYPE GetType(void) = 0;

	void update(void);
	
	KeyPair GetInput(TRG_STATE trg)
	{
		return _keyData[intCast(trg)];
	};
	bool GetInput(TRG_STATE trg, DIR dir)
	{
		return _touchData[intCast(trg)][intCast(dir)];
	};
	DIR GetDIR(void)
	{
		return _dirData;
	}
protected:
	//bool data[static_cast<int>(DIR::MAX)];
	TRG_ArrayKey _keyData;
	TRG_ArrayTouch _touchData;

	DIR _dirData;
	//std::array<std::pair<DIR, TRG_KEY>, static_cast<int>(DIR::MAX)>data;
};

DIR begin(DIR);
DIR end(DIR);
DIR operator*(DIR key);
DIR operator++(DIR & key);