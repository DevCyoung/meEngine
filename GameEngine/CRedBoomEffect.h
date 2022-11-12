#pragma once
#include "CEffect.h"
class CRedBoomEffect :
    public CEffect
{
public:
	virtual void OnShootPlay(Vector2 pos, bool isFlipX) override;

	CLONE(CRockmanObj);

public:
	CRedBoomEffect();
	CRedBoomEffect(const CRedBoomEffect& _other);
	~CRedBoomEffect();
};

