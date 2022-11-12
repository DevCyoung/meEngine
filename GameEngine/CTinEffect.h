#pragma once
#include "CEffect.h"
class CTinEffect :
    public CEffect
{

public:
	virtual void tick() override;
	virtual void render(HDC _dc) override;
	virtual void OnShootPlay(Vector2 pos, bool isFlipX) override;

	CLONE(CRockmanObj);

public:
	CTinEffect();
	CTinEffect(const CTinEffect& _other);
	~CTinEffect();
};

