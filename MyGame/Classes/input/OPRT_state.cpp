#include "OPRT_state.h"

OPRT_state::OPRT_state()
{
	for (auto itr : DIR())
	{
		data[static_cast<int>(itr)].first = false;
		//data[static_cast<int>(DIR::UP)].second = TRG_KEY::NEW;
	}
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
