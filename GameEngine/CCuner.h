#pragma once
#include "CRockmanMonster.h"
class CCuner :
    public CRockmanMonster
{

public:


	//virtual void tick() override;
	//virtual void fixed_tick() override;
	//virtual void render(HDC _dc) override;

	////box 
	//virtual void OnTriggerEnter(CCollider* _pOhter);
	//virtual void OnTriggerStay(CCollider* _pOhter);
	//virtual void OnTriggerExit(CCollider* _pOhter);

	CLONE(CCuner);

public:
	CCuner();
	CCuner(const CCuner& _other);
	~CCuner();
};

