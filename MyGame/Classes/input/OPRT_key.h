#pragma once
#include "OPRT_state.h"
struct OPRT_key : public OPRT_state
{
	OPRT_key(cocos2d::Node* sp);
	//void Update();				// ｷｰの追加処理(ﾄﾘｶﾞｰ処理)
	OPRT_TYPE GetType(void)override;	// 今使っている入力ﾀｲﾌﾟを取得(これはkey)
};

