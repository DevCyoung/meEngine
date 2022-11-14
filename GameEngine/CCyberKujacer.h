#pragma once
#include "CRockmanMonster.h"

enum class CYBERBOSS_STATE
{
	IDLE,
	ENTER,
	ATTACK1,
	ATTACK2,
	ATTACK3,
	ATTACK3SHOOT,
	ATTACK2READY,
	
	MOVEINVISIBLE,
	MOVEVISIBLE
};



class CZero;

class CCyberKujacer :
    public CRockmanMonster
{
public:
	CZero* m_zero;
	float		m_ultimateTime;
	float		m_curUltimateTime;
	int			m_reciveAttackCnt;
	Vector2		m_targetPos;

	CYBERBOSS_STATE	m_bossState;
	float		m_stateDelay;

	int			m_randomAttack;

	virtual void tick() override;
	virtual void fixed_tick() override;
	virtual void render(HDC _dc) override;

	//box 
	virtual void OnTriggerEnter(CCollider* _pOhter);
	virtual void OnTriggerStay(CCollider* _pOhter);
	virtual void OnTriggerExit(CCollider* _pOhter);

	

	//
	void MoveEvent();
	void LandAttack1Event();
	void Attack2Event();
	void Attack3Event();

	void Attack3EventMissile();

	CLONE(CCyberKujacer);

public:
	CCyberKujacer();
	CCyberKujacer(const CCyberKujacer& _other);
	~CCyberKujacer();

};

