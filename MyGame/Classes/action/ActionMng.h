#pragma once
#include <cocos2d.h>
#include <map>
#include <functional>
#include <input/OPRT_state.h>


enum class ACT_STATE
{
	RUN,
	JUMP,
	JUMPING,
	FALL,
	FALLING,
	IDLE,
	CHANGE_RIGHT,
	CHANGE_LEFT,
	SHOT
};

struct actModule;
using funcActModule = std::function<bool(cocos2d::Sprite&, actModule&)>;

struct actModule
{
	ACT_STATE actID;							// �����ID
	std::list<ACT_STATE>white;					// �ܲ�ؽ�
	std::list<ACT_STATE>black;					// ��ׯ�ؽ�
	std::list<funcActModule>act;				// �����n�̱����
	funcActModule runAction;					// ���s���鱸���	
	cocos2d::Vec2 speed;						// �ړ����x
	std::array<cocos2d::Size, 2> colSize;		// �����蔻��̻���
	TRG_STATE keyMode;							// ���͂�����@ ��������
	Timing keyTiming;							// �������ݸ�
	INPUT_ID inputID;							// ���̎��
};

class ActionMng
{
public:
	ActionMng();
	//ActionMng(cocos2d::Sprite& sp);
	~ActionMng();
	void AddActModule(const std::string& actName, actModule& module);	// ����݂̾��
	void update(cocos2d::Sprite& sp);

	std::map<std::string, actModule>_moduleMap;

	// �ϐ�
	ACT_STATE nowAct;	// ���݂̱����
};

