#pragma once
#include "CEffect.h"
class CLandDash :
    public CEffect
{
public:
	virtual void OnShootPlay(Vector2 pos, bool isFlipX) override;

	CLONE(CRockmanObj);

public:
	CLandDash();
	CLandDash(const CLandDash& _other);
	~CLandDash();
};

