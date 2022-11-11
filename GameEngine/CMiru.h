#pragma once
#include "CRockmanMonster.h"
class CMiru :
    public CRockmanMonster
{
	

public:
	virtual void tick() override;
	virtual void fixed_tick() override;
	virtual void render(HDC _dc) override;

	//box 
	virtual void OnTriggerEnter(CCollider* _pOhter);
	virtual void OnTriggerStay(CCollider* _pOhter);
	virtual void OnTriggerExit(CCollider* _pOhter);

	CLONE(CMiru);

public:
	CMiru();
	CMiru(const CMiru& _other);
	~CMiru();

};

