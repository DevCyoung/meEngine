#pragma once
#include "CGameObject.h"
class CRockmanObj :
    public CGameObject
{
public:
	virtual void tick() override;
	virtual void fixed_tick() {};
	virtual void render(HDC _dc) override;
	virtual void OnTriggerEnter(CCollider* _pOhter);
	virtual void OnTriggerStay(CCollider* _pOhter);
	virtual void OnTriggerExit(CCollider* _pOhter);


	CLONE(CRockmanObj);

public:
	CRockmanObj();
	CRockmanObj(const CRockmanObj& _other);
	~CRockmanObj();

};

