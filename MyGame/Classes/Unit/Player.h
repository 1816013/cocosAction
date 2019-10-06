#pragma once
#include "Obj.h"

class Player :
	public Obj
{
public:
	Player();
	~Player();
	void Init(void);					// ‰Šú‰»@½Ìß×²Äì¬‚È‚Ç
	void Update(bool dir)override;		// ½Ìß×²Ä‚ÌˆÚ“®‚È‚Ç
private:
	Sprite* sprite;
};

