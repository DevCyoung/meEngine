#pragma once
#include "CEffect.h"
class CWallHitEffect :
    public CEffect
{
public:
	virtual void OnShootPlay(Vector2 pos, bool isFlipX) override;

	CLONE(CRockmanObj);

public:
	CWallHitEffect();
	CWallHitEffect(const CWallHitEffect& _other);
	~CWallHitEffect();
};

