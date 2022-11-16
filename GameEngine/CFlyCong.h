#pragma once
#include "CRockmanMonster.h"

class CCyberCongBoost;

enum class BOOSTSTATE
{
	PATROL,
	ATTACK,
	ATTACKREADY,
	END,
};

class CFlyCong :
    public CRockmanMonster
{
public:

	CCyberCongBoost* m_boost;
	BOOSTSTATE		m_booState;
	virtual void tick() override;

	float	m_delay[(UINT)BOOSTSTATE::END];
	

	CLONE(CFlyCong);

public:
	CFlyCong();
	CFlyCong(const CFlyCong& _other);
	~CFlyCong();

};

