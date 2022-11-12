#pragma once
#include "CEffect.h"

class CSliceEffect :
    public CEffect
{
public:
	virtual void OnShootPlay(Vector2 pos, bool isFlipX) override;

	CLONE(CRockmanObj);

public:
	CSliceEffect();
	CSliceEffect(const CSliceEffect& _other);
	~CSliceEffect();
};

