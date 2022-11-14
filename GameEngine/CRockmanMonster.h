#pragma once
#include "CRockmanObj.h"

class CMonsterHitBox;
class CZero;

class CRockmanMonster :
    public CRockmanObj
{

public:
	CMonsterHitBox* m_hitBox;
	CZero*			m_zero;
	float			m_startLen;
	float			m_CurstartLen;
	Vector2			m_vecLen;
	Vector2			m_vecDir;
	bool			m_isStart;

public:
	virtual void tick() override;
	virtual void fixed_tick() override;
	virtual void render(HDC _dc) override;

	//box 
	virtual void OnTriggerEnter(CCollider* _pOhter) override;
	virtual void OnTriggerStay(CCollider* _pOhter) override;
	virtual void OnTriggerExit(CCollider* _pOhter) override;


public:
	virtual void Save(FILE *pFile);
	virtual void Load(FILE* pFile);
	CLONE(CRockmanObj);

public:
	CRockmanMonster();
	CRockmanMonster(const CRockmanMonster& _other);
	~CRockmanMonster();

};

