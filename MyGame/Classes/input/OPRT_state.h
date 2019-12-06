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

enum class INPUT_ID	// •ûŒü
{
	UP,			// ã
	RIGHT,		// ‰E
	DOWN,		// ‰º
	LEFT,		// ¶
	SHOT,
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

//using DIR_ArrayTouch =  std::array<bool, intCast(INPUT_ID::MAX)>;
//using TRG_ArrayTouch = std::array<DIR_ArrayTouch, intCast(TRG_STATE::MAX)>;
//using KeyPair = std::pair<bool, cocos2d::EventKeyboard::KeyCode>;
using KeyMap = std::map<cocos2d::EventKeyboard::KeyCode, bool>;
//using DIR_ArrayKey = std::array<KeyPair, intCast(DIR::MAX)>;
using TRG_ArrayKey = std::array<KeyMap, intCast(TRG_STATE::MAX)>;

struct OPRT_state
{
	OPRT_state();
	virtual OPRT_TYPE GetType(void) = 0;

	void update(void);
	
	bool GetInput(TRG_STATE trg, INPUT_ID inputID)
	{
		return _keyData[intCast(trg)][inputTbl[static_cast<int>(inputID)]];
	};
protected:
	TRG_ArrayKey _keyData;
	cocos2d::EventKeyboard::KeyCode inputTbl[static_cast<int>(INPUT_ID::MAX)];
};

INPUT_ID begin(INPUT_ID);
INPUT_ID end(INPUT_ID);
INPUT_ID operator*(INPUT_ID key);
INPUT_ID operator++(INPUT_ID & key);