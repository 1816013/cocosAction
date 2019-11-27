#pragma once
#include "cocos2d.h"
#include <array>
#include <map>

#define intCast(tag) static_cast<int>(tag)

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

enum class Timing
{
	ON,
	ON_MOM,
	OFF,
	OFF_MOM
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
using KeyMap = std::map<cocos2d::EventKeyboard::KeyCode, bool>;
//using DIR_ArrayKey = std::array<KeyPair, intCast(DIR::MAX)>;
using TRG_ArrayKey = std::array<KeyMap, intCast(TRG_STATE::MAX)>;

struct OPRT_state
{
	OPRT_state();
	virtual OPRT_TYPE GetType(void) = 0;

	void update(void);
	
	bool GetInput(TRG_STATE trg, cocos2d::EventKeyboard::KeyCode keyCode)
	{
		return _keyData[intCast(trg)][keyCode];
	};
	bool GetInput(TRG_STATE trg, DIR dir)
	{
		return _touchData[intCast(trg)][intCast(dir)];
	};
protected:
	TRG_ArrayKey _keyData;
	TRG_ArrayTouch _touchData;
};

DIR begin(DIR);
DIR end(DIR);
DIR operator*(DIR key);
DIR operator++(DIR & key);