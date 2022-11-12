#include "pch.h"
#include "CWallHitEffect.h"
#include "CAnimation.h"
#include "CAnimator.h"

#include "CTimeManager.h"

CWallHitEffect::CWallHitEffect()
{
	GetAnimator()->LoadAnimation(L"animation\\effect\\chareffect\\wallfoothit.anim");
	//GETINSTANCE(CTimeManager)->SetDelayTime(0.2f);
}

CWallHitEffect::CWallHitEffect(const CWallHitEffect& _other)
{
}

CWallHitEffect::~CWallHitEffect()
{
}


void CWallHitEffect::OnShootPlay(Vector2 pos, bool isFlipX)
{
	if (isFlipX == true)
	{
		pos.x += -62.f;
	}
	else
	{
		pos.x += 62.f;
	}
	pos.y += 40.f;
	CEffect::OnShootPlay(pos, isFlipX);
	GetAnimator()->Play(L"WALLFOOTHIT", false);
}

