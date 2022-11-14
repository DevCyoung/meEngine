#pragma once
#include "CEffect.h"

class CZero;
class CCyberKujacer;
class CCyberTargetEffect :
    public CEffect
{
public:
	CZero* m_zero;
	CCyberKujacer* m_boss;


	virtual void OnShootPlay(Vector2 pos, bool isFlipX) override;
	virtual void tick() override;
	virtual void render(HDC _dc) override;
	CLONE(CRockmanObj);

public:
	CCyberTargetEffect();
	CCyberTargetEffect(const CCyberTargetEffect& _other);
	~CCyberTargetEffect();
};

