#pragma once
#include "CRockmanMonster.h"


enum class GOSM_STATE
{
	ATTACK,
	ATTACKREADY,
	IDLE,
};


class CGosm :
    public CRockmanMonster
{
public:
	virtual void tick() override;
	virtual void fixed_tick() override;
	virtual void render(HDC _dc) override;

	float		 m_time;
	GOSM_STATE	m_state;

	CLONE(CGosm);

public:
	CGosm();
	CGosm(const CGosm& _other);
	~CGosm();
};

