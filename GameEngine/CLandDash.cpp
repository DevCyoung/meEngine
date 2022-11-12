#include "pch.h"
#include "CLandDash.h"
#include "CAnimator.h"
#include "CAnimation.h"



CLandDash::CLandDash()
{
	GetAnimator()->LoadAnimation(L"animation\\effect\\chareffect\\landdash.anim");
	m_renderPer = 3.0f;
}

CLandDash::CLandDash(const CLandDash& _other)
{

}


CLandDash::~CLandDash()
{
}

void CLandDash::OnShootPlay(Vector2 pos, bool isFlipX)
{
	CEffect::OnShootPlay(pos, isFlipX);
	GetAnimator()->Play(L"LANDDASH", false);
}