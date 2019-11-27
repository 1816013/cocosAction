#include "OPRT_state.h"

OPRT_state::OPRT_state()
{
	cocos2d::EventKeyboard::KeyCode dirTbl[static_cast<int>(DIR::MAX)] =
	{
		cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW,
		cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW,
		cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW,
		cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW
	};

	for (auto dir : DIR())
	{
		_keyData[static_cast<int>(TRG_STATE::INPUT)].emplace(dirTbl[static_cast<int>(dir)], false);
	};
	for (int trg = 0; trg < static_cast<int>(TRG_STATE::MAX); trg++)
	{
		//_keyData[trg][] = false;
		for (auto itr : DIR())
		{
			_touchData[static_cast<int>(trg)][static_cast<int>(itr)] = false;
		}
	}
}

void OPRT_state::update(void)
{	
	_keyData[static_cast<int>(TRG_STATE::OLD)] = _keyData[static_cast<int>(TRG_STATE::NOW)];
	_keyData[static_cast<int>(TRG_STATE::NOW)] = _keyData[static_cast<int>(TRG_STATE::INPUT)];
}

DIR begin(DIR)
{
	return DIR::UP;
}

DIR end(DIR)
{
	return DIR::MAX;
}

DIR operator*(DIR key)
{
	return key;
}

DIR operator++(DIR & key)
{
	return key = DIR(std::underlying_type<DIR>::type(key) + 1);
}
