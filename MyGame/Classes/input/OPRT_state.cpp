#include "OPRT_state.h"

OPRT_state::OPRT_state()
{
	_dirData = DIR::NEUTRAL;
	for (int trg = 0; trg < static_cast<int>(TRG_STATE::MAX); trg++)
	{
		_keyData[trg].first = false;
		for (auto itr : DIR())
		{
			_touchData[static_cast<int>(trg)][static_cast<int>(itr)] = false;
		}
	}
}

void OPRT_state::update(void)
{	
	_keyData[intCast(TRG_STATE::OLD)] = _keyData[intCast(TRG_STATE::NOW)];
	_keyData[intCast(TRG_STATE::NOW)] = _keyData[intCast(TRG_STATE::INPUT)];
}

DIR begin(DIR)
{
	return DIR::NEUTRAL;
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
