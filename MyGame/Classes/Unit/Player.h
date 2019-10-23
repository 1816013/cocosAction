#pragma once
#include "Obj.h"
#include "input/OPRT_state.h"
#include <vector>
#include <array>
#include <Colision.h>

#define intCast(tag) static_cast<int>(tag)
enum class Tag
{
	ANIM,		// ��Ұ���
	ACT,		// �����(1�ڰі��ɓ���������)
	TRG_ACT		// �����(���̎���������������)
};


enum class ConerPos
{
	LEFT_UP,
	RIGHT_UP,
	LEFT_DOWN,
	RIGHT_DOWN,
	MAX
};


class Player : public Sprite
{
public:
	static cocos2d::Sprite* createSprite();
	Player();
	~Player();
	bool init()override;				// �������@���ײč쐬�Ȃ�
	void update(float delta)override;		// ���ײĂ̈ړ��Ȃ�
	CREATE_FUNC(Player);
private:
	Vec2 _pos;
	bool LRflag;					// ���E�m�F�p�@�E:false ��:true
	bool oldLRflag = false;			// 1�ڰёO�ɉE�ƍ��ǂ���������Ă�����
	bool jumpFlag;					// �ެ������݂������ꂽ��@�폜�\��
	bool jumpFancFlag = false;		// �ެ��ߒ�:true	�ެ��߂��Ă��Ȃ���:false

	Size tileSize;// ��ق̑傫��
	Size mapTile;// ϯ�߂���ِ���ڂ�x, ��ڂ�y

	//std::vector<int>colGID;
	std::array<Vec2, static_cast<int>(ConerPos::MAX)>_cPos;
	std::unique_ptr<OPRT_state>_inputState;
	Animation* oldanim;

	int hitc = 0;

	//std::unique_ptr<Colision>col;
	Colision col;
	//bool Colision(const Vec2 ID, TMXLayer & col);
	//bool AnimCreate(std::string key, int cnt, float time);
};

