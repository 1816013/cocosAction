#pragma once
#include "OPRT_state.h"
struct OPRT_touch : public OPRT_state
{
	OPRT_touch(cocos2d::Node* sp);
	OPRT_TYPE GetType(void)override;	// 今使っている入力ﾀｲﾌﾟを取得(これはtouch)
private:
	cocos2d::Point _startTPos;
};

