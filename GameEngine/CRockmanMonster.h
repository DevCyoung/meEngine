#pragma once
#include "CRockmanObj.h"
class CRockmanMonster :
    public CRockmanObj
{

public:
	virtual void tick() override;
	virtual void fixed_tick() override;
	virtual void render(HDC _dc) override;

	CLONE(CRockmanObj);

public:
	CRockmanMonster();
	CRockmanMonster(const CRockmanMonster& _other);
	~CRockmanMonster();

};

