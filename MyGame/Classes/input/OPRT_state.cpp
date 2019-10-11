#include "OPRT_state.h"

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
