#pragma once
#include "CRockmanMonster.h"

class CZero;

class CCyberMissile :
    public CRockmanMonster
{
public:
	float		m_lifeTIme;
	float		m_deadTime;
	bool		m_isBall;
	virtual void tick() override;
	virtual void fixed_tick() override;
	virtual void render(HDC _dc) override;


	//box 
	virtual void OnTriggerEnter(CCollider* _pOhter);
	virtual void OnTriggerStay(CCollider* _pOhter);
	virtual void OnTriggerExit(CCollider* _pOhter);

	CZero* m_zero;

	CLONE(CCyberMissile);

public:
	CCyberMissile();
	CCyberMissile(const CCyberMissile& _other);
	~CCyberMissile();
};

