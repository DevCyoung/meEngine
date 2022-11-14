#pragma once
#include "CRockmanMonster.h"

enum class CONG_STATE
{
	NONE,
	IDLE,
	MOVE,
	PATROL,
	FALLING,
	JUMP,
	HIDE,
	ATTACK,
	END
};


class CCong :
    public CRockmanMonster
{
public:

	CONG_STATE	m_state;
	float		m_time[(UINT)CONG_STATE::END];
	Vector2		m_move;

	virtual void tick() override;
	virtual void fixed_tick() override;
	virtual void render(HDC _dc) override;

	//box 
	virtual void OnTriggerEnter(CCollider* _pOhter);
	virtual void OnTriggerStay(CCollider* _pOhter);
	virtual void OnTriggerExit(CCollider* _pOhter);

	void ToPatrol();
	void ToHide();
	void ToAttack();
	void ToFalling();

	void BulletEvent();

	CLONE(CCong);

public:
	CCong();
	CCong(const CCong& _other);
	~CCong();
};

