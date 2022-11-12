#include "pch.h"
#include "CTinEffect.h"
#include "CAnimator.h"
#include "CAnimation.h"

CTinEffect::CTinEffect()
{
	GetAnimator();
	GetAnimator()->LoadAnimation(L"animation\\effect\\tin.anim");
	m_renderPer = 2.5f;
}

CTinEffect::CTinEffect(const CTinEffect& _other)
{

}

CTinEffect::~CTinEffect()
{

}


void CTinEffect::tick()
{
	if (m_isUsing == false)
	{
		return;
	}

	CEffect::tick();
}

void CTinEffect::render(HDC _dc)
{
	if (m_isUsing == false)
	{
		return;
	}

	CEffect::render(_dc);
}

void CTinEffect::OnShootPlay(Vector2 pos, bool isFlipX)
{
	if (isFlipX)
	{
		pos.x += 20.f;
	}
	else
	{
		pos.x -= 20.f;
	}
	CEffect::OnShootPlay(pos, isFlipX);
	GetAnimator()->Play(L"TIN", false);	
}
