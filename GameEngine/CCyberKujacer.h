#pragma once
#include "CRockmanMonster.h"

enum class CYBERBOSS_STATE
{
	IDLE,
	SPON,
	ENTER,
	ATTACK1,
	ATTACK2,
	ATTACK3,
	ATTACK3SHOOT,
	ATTACK2READY,
	HPZERO,
	MOVEINVISIBLE,
	BOOMSHOOTS,
	MOVEVISIBLE
};



class CZero;
class CMonsterHpbar;

class CCyberKujacer :
    public CRockmanMonster
{
public:
	CZero*		m_zero;
	float		m_ultimateTime;
	float		m_curUltimateTime;
	int			m_reciveAttackCnt;
	CMonsterHpbar* m_hpBar;
	Vector2		m_targetPos;

	CYBERBOSS_STATE	m_bossState;

	float			m_stateDelay;
	float			m_destTime;
	int				m_destCount;

	int			m_randomAttack;

	virtual void tick() override;
	virtual void fixed_tick() override;
	virtual void render(HDC _dc) override;

	//box 
	virtual void OnTriggerEnter(CCollider* _pOhter);
	virtual void OnTriggerStay(CCollider* _pOhter);
	virtual void OnTriggerExit(CCollider* _pOhter);

	virtual void Die() override;

	//
	void MoveEvent();
	void LandAttack1Event();
	void Attack2Event();
	void Attack3Event();
	void Attack3EventMissile();

	void EnterEvent();
	void TingEvent();

	CLONE(CCyberKujacer);

public:
	CCyberKujacer();
	CCyberKujacer(const CCyberKujacer& _other);
	~CCyberKujacer();

};

