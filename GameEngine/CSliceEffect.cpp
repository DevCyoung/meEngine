#include "pch.h"
#include "CSliceEffect.h"
#include "CAnimator.h"

CSliceEffect::CSliceEffect()
{	
	GetAnimator()->LoadAnimation(L"animation\\effect\\verticalslice.anim");	
	GetAnimator()->LoadAnimation(L"animation\\effect\\slopslice.anim");
}

CSliceEffect::CSliceEffect(const CSliceEffect& _other)
{
}

CSliceEffect::~CSliceEffect()
{
}


void CSliceEffect::OnShootPlay(Vector2 pos, bool isFlipX)
{
	CEffect::OnShootPlay(pos, isFlipX);
	if (rand() % 2 == 0)
	{
		GetAnimator()->Play(L"SLOPSLICE", false);
	}
	else
	{
		GetAnimator()->Play(L"VERTICALSLICE", false);
	}
	
}

