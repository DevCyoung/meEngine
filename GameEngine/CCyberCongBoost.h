#pragma once
#include "CRockmanMonster.h"
class CCyberCongBoost :
    public CRockmanMonster
{
public:
	Vector2			m_offset;
	CRockmanObj*    m_target;
	bool			m_isMove;


	virtual void tick() override;


	CLONE(CCyberCongBoost);

public:
	CCyberCongBoost();
	CCyberCongBoost(const CCyberCongBoost& _other);
	~CCyberCongBoost();
};

