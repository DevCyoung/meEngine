#include "pch.h"
#include "CRedBoomEffect.h"
#include "CAnimation.h"
#include "CAnimator.h"


CRedBoomEffect::CRedBoomEffect()
{
	GetAnimator()->LoadAnimation(L"animation\\effect\\boomred.anim");
}


CRedBoomEffect::~CRedBoomEffect()
{

}

CRedBoomEffect::CRedBoomEffect(const CRedBoomEffect& _other)
{
}

void CRedBoomEffect::OnShootPlay(Vector2 pos, bool isFlipX)
{
	CEffect::OnShootPlay(pos, isFlipX);
	GetAnimator()->Play(L"BOOMRED", false);
}

