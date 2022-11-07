#pragma once
#include "CRockmanMonster.h"

class CTry :
	public CRockmanMonster
{


public:
	virtual void tick() override;
	virtual void fixed_tick() override;
	virtual void render(HDC _dc) override;

	CLONE(CTry);

public:
	CTry();
	CTry(const CTry& _other);
	~CTry();

};

