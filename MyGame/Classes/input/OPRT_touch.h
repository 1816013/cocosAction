#pragma once
#include "OPRT_state.h"
struct OPRT_touch : public OPRT_state
{
	OPRT_touch(Node* sp);
	//void Update();			// ﾀｯﾁ操作
	OPRT_TYPE GetType(void)override;	// 今使っている入力ﾀｲﾌﾟを取得(これはtouch)
private:
	Point _startTPos;
};

