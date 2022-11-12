#pragma once
#include "CEffect.h"

class CPlayerController;
class CZero;

class CDashPowerEffect :
    public CEffect
{
public:
	CZero* m_zero;

	virtual void OnShootPlay(Vector2 pos, bool isFlipX) override;
	virtual void tick() override;
	virtual void render(HDC _dc) override;
	CLONE(CRockmanObj);

public:
	CDashPowerEffect();
	CDashPowerEffect(const CDashPowerEffect& _other);
	~CDashPowerEffect();
};

