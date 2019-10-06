#pragma once
#include "Obj.h"

class Player :
	public Obj
{
public:
	Player();
	~Player();
	void Init(void);					// 初期化　ｽﾌﾟﾗｲﾄ作成など
	void Update(bool dir)override;		// ｽﾌﾟﾗｲﾄの移動など
private:
	Sprite* sprite;
};

