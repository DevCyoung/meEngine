#pragma once
#include "CEffect.h"
class CZeroDieBall :
    public CEffect
{
public:
	virtual void tick() override;
	virtual void OnShootPlay(Vector2 pos, bool isFlipX) override;
	Vector2	m_dir;
	float	m_timeDelay;
	CLONE(CRockmanObj);

public:
	CZeroDieBall();
	CZeroDieBall(const CZeroDieBall& _other);
	~CZeroDieBall();
};

