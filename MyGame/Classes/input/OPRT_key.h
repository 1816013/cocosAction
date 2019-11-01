#pragma once
#include "OPRT_state.h"
struct OPRT_key : public OPRT_state
{
	OPRT_key(Node* sp);
	void Update()override;				// ｷｰの追加処理(ﾄﾘｶﾞｰ処理)
	OPRT_TYPE GetType(void)override;	// 今使っている入力ﾀｲﾌﾟを取得(これはkey)
	void SetTrg(DIR dir, KEY_MODE trg);			// ﾄﾘｶﾞｰの設定
};

