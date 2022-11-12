#pragma once
#include "CEffect.h"
class CSlideDustEffect :
    public CEffect
{

public:	
	virtual void OnShootPlay(Vector2 pos, bool isFlipX) override;

	CLONE(CRockmanObj);

public:
	CSlideDustEffect();
	CSlideDustEffect(const CSlideDustEffect& _other);
	~CSlideDustEffect();
};

