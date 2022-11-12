#include "pch.h"
#include "CSlideDustEffect.h"
#include "CAnimation.h"
#include "CAnimator.h"


CSlideDustEffect::CSlideDustEffect()
{
	GetAnimator();
	GetAnimator()->LoadAnimation(L"animation\\effect\\chareffect\\wallsliddust.anim");
}



CSlideDustEffect::CSlideDustEffect(const CSlideDustEffect& _other)
{
}


CSlideDustEffect::~CSlideDustEffect()
{
}

void CSlideDustEffect::OnShootPlay(Vector2 pos, bool isFlipX)
{
	CEffect::OnShootPlay(pos, isFlipX);
	GetAnimator()->Play(L"WALLSLIDDUST", false);
}